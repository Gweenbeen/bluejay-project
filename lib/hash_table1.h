// hash_table.h - Hash Table API

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define GROUP_WIDTH 8
#define CTRL_EMPTY   ((int8_t)0x80) // 0b10000000
#define CTRL_DELETED ((int8_t)0xFE) // 0b11111110

typedef struct {
    const char *name; // Identifier string (not owned, or arena-allocated)
    size_t len;       // Length of identifier
    void *symbol;     // Pointer to your AST/Type/Symbol struct
} SymEntry;

typedef struct {
    int8_t *ctrl;       // Array of (capacity + GROUP_WIDTH) control bytes
    SymEntry *slots;    // Array of (capacity) entries
    size_t capacity;    // Always a power of 2 >= 8
    size_t size;        // Active symbols
    size_t growth_left; // Remaining slots before resize (87.5% max load)
} SymTable;

void symtab_init(SymTable *t, size_t initial_cap);
void symtab_free(SymTable *t);
bool symtab_insert(SymTable *t, const char *name, size_t len, void *symbol);
void *symtab_lookup(const SymTable *t, const char *name, size_t len);
bool symtab_delete(SymTable *t, const char *name, size_t len);

static uint64_t hash_str(const char *str, size_t len) {
    uint64_t h = 14695981039346656037ULL;
    for (size_t i = 0; i < len; i++) {
        h ^= (uint8_t)str[i];
        h *= 1099511628211ULL;
    }
    // Finalize mix so upper (H1) and lower (H2) bits are uncorrelated
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccdULL;
    h ^= h >> 33;
    return h;
}

static inline void set_ctrl(SymTable *t, size_t idx, int8_t val) {
    t->ctrl[idx] = val;
    // Mirror the first 8 bytes to the end so unaligned 8-byte loads wrap safely
    if (idx < GROUP_WIDTH) {
        t->ctrl[idx + t->capacity] = val;
    }
}

// Load 8 control bytes unaligned into a 64-bit integer
static inline uint64_t load_group(const int8_t *ctrl) {
    uint64_t val;
    memcpy(&val, ctrl, sizeof(val)); // Compiles to a single MOV instruction
    return val;
}

// Returns a 64-bit mask where the top bit (0x80) of each matching byte is 1
static inline uint64_t match_byte(uint64_t group, int8_t byte) {
    uint64_t pattern = 0x0101010101010101ULL * (uint8_t)byte;
    uint64_t x = group ^ pattern;
    return (x - 0x0101010101010101ULL) & ~x & 0x8080808080808080ULL;
}

// Both CTRL_EMPTY (0x80) and CTRL_DELETED (0xFE) have their top bit set to 1
static inline uint64_t match_empty_or_deleted(uint64_t group) {
    return group & 0x8080808080808080ULL;
}

// Extracts the byte index (0..7) of the lowest set match bit, then clears it
static inline int next_match(uint64_t *mask) {
    int bit = __builtin_ctzll(*mask);
    *mask &= (*mask - 1);
    return bit >> 3; // Divide bit position by 8 to get byte index
}

void symtab_init(SymTable *t, size_t initial_cap) {
    size_t cap = 8;
    while (cap < initial_cap) cap *= 2;

    t->capacity = cap;
    t->size = 0;
    t->growth_left = (cap * 7) / 8;
    t->ctrl = malloc(cap + GROUP_WIDTH);
    memset(t->ctrl, CTRL_EMPTY, cap + GROUP_WIDTH);
    t->slots = calloc(cap, sizeof(SymEntry));
}

void symtab_free(SymTable *t) {
    free(t->ctrl);
    free(t->slots);
    t->ctrl = NULL;
    t->slots = NULL;
}

void *symtab_lookup(const SymTable *t, const char *name, size_t len) {
    if (t->size == 0) return NULL;

    uint64_t hash = hash_str(name, len);
    size_t mask = t->capacity - 1;
    size_t pos = (hash >> 7) & mask;   // H1
    int8_t h2 = (int8_t)(hash & 0x7F); // H2

    size_t step = 0;
    while (true) {
        uint64_t group = load_group(&t->ctrl[pos]);
        uint64_t matches = match_byte(group, h2);

        while (matches) {
            int offset = next_match(&matches);
            size_t idx = (pos + offset) & mask;
            if (t->slots[idx].len == len &&
                memcmp(t->slots[idx].name, name, len) == 0) {
                return t->slots[idx].symbol;
            }
        }

        // If any slot in this group is EMPTY, the symbol does not exist
        if (match_byte(group, CTRL_EMPTY)) {
            return NULL;
        }

        step += GROUP_WIDTH;
        pos = (pos + step) & mask;
    }
}

static void symtab_resize(SymTable *t, size_t new_cap) {
    SymTable next;
    symtab_init(&next, new_cap);

    for (size_t i = 0; i < t->capacity; i++) {
        // Top bit 0 means the slot is Full
        if ((t->ctrl[i] & 0x80) == 0) {
            symtab_insert(&next, t->slots[i].name, t->slots[i].len, t->slots[i].symbol);
        }
    }

    symtab_free(t);
    *t = next;
}

bool symtab_insert(SymTable *t, const char *name, size_t len, void *symbol) {
    if (t->growth_left == 0) {
        // If many tombstones exist, rehash at same size; otherwise double
        size_t new_cap = (t->size >= (t->capacity * 7) / 16) ? t->capacity * 2 : t->capacity;
        symtab_resize(t, new_cap);
    }

    uint64_t hash = hash_str(name, len);
    size_t mask = t->capacity - 1;
    size_t pos = (hash >> 7) & mask;
    int8_t h2 = (int8_t)(hash & 0x7F);

    size_t step = 0;
    while (true) {
        uint64_t group = load_group(&t->ctrl[pos]);

        // 1. Check if symbol already exists (update in place)
        uint64_t matches = match_byte(group, h2);
        while (matches) {
            int offset = next_match(&matches);
            size_t idx = (pos + offset) & mask;
            if (t->slots[idx].len == len &&
                memcmp(t->slots[idx].name, name, len) == 0) {
                t->slots[idx].symbol = symbol;
                return false; // Updated existing
            }
        }

        // 2. Otherwise, claim the first Empty or Deleted slot in this group
        uint64_t avail = match_empty_or_deleted(group);
        if (avail) {
            int offset = next_match(&avail);
            size_t idx = (pos + offset) & mask;
            if (t->ctrl[idx] == CTRL_EMPTY) {
                t->growth_left--; // Only Empty slots consume growth_left
            }
            set_ctrl(t, idx, h2);
            t->slots[idx] = (SymEntry){ .name = name, .len = len, .symbol = symbol };
            t->size++;
            return true; // Inserted new
        }

        step += GROUP_WIDTH;
        pos = (pos + step) & mask;
    }
}

bool symtab_delete(SymTable *t, const char *name, size_t len) {
    if (t->size == 0) return false;

    uint64_t hash = hash_str(name, len);
    size_t mask = t->capacity - 1;
    size_t pos = (hash >> 7) & mask;
    int8_t h2 = (int8_t)(hash & 0x7F);

    size_t step = 0;
    while (true) {
        uint64_t group = load_group(&t->ctrl[pos]);
        uint64_t matches = match_byte(group, h2);

        while (matches) {
            int offset = next_match(&matches);
            size_t idx = (pos + offset) & mask;
            if (t->slots[idx].len == len &&
                memcmp(t->slots[idx].name, name, len) == 0) {
                t->size--;
                if (match_byte(group, CTRL_EMPTY)) {
                    set_ctrl(t, idx, CTRL_EMPTY);
                    t->growth_left++;
                } else {
                    set_ctrl(t, idx, CTRL_DELETED);
                }
                return true;
            }
        }

        if (match_byte(group, CTRL_EMPTY)) {
            return false;
        }

        step += GROUP_WIDTH;
        pos = (pos + step) & mask;
    }
}

void t(void)
{
	SymTable st = {0};
	symtab_init(&st, 8);

	int sym_x = 10, sym_y = 20;
	symtab_insert(&st, "player_x", 8, &sym_x);
	symtab_insert(&st, "player_y", 8, &sym_y);

	assert(symtab_lookup(&st, "player_x", 8) == &sym_x);
	assert(symtab_lookup(&st, "unknown", 7) == NULL);

	symtab_delete(&st, "player_x", 8);
	assert(symtab_lookup(&st, "player_x", 8) == NULL);

	symtab_free(&st);
	
	printf("All symbol table tests passed!\n");
}