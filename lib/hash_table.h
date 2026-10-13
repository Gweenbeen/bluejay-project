// hash_table.h - Hash indexed table API

#pragma once

// HashTableEntry :: Entry in HashTable
struct HashTableEntry
{
	struct StringView *key;
	const uint8_t *value;
	int16_t probe_dist;
	uint8_t small_hash;
};

// HashTable :: Hash table header
struct HashTable
{
	struct HashTableEntry *entries;
	size_t length;
	size_t capacity;

	alignas(max_align_t) uint8_t inline_memory[16];
};

INLINE void hash_table_init(struct HashTable *self);
INLINE void hash_table_free(struct HashTable *self);
INLINE void hash_table_reset(struct HashTable *self);
INLINE void hash_table_rehash(struct HashTable *self);
INLINE void hash_table_resize(struct HashTable *self, size_t length);
INLINE struct StringTable *hash_table_copy(struct HashTable *src);
INLINE const uint8_t *hash_table_at(struct HashTable *self, size_t index);
INLINE const uint8_t *hash_table_find(struct HashTable *self, const uint8_t *item);
INLINE void hash_table_place(struct HashTable *self, const uint8_t *item);
INLINE void hash_table_insert(struct HashTable *self, const uint8_t *item);