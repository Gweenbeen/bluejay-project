// arena.h - Bump allocator API

#pragma once

#include <stddef.h>
#include <stdint.h>

// ArenaBlock :: Doubly linked list of memory region
struct ArenaBlock
{
	uint8_t *ptr;
	size_t used;

	struct ArenaBlock *prev;
	struct ArenaBlock *next;
};

// Arena :: Header for arena blocks 
struct Arena
{
	size_t initial_capacity;
	struct ArenaBlock *head;
	struct ArenaBlock *tail;
	struct ArenaBlock *current;

	alignas(max_align_t) uint8_t inline_meomry[8];
};

#define ALIGN_ADDRESS_POW(addr, align) ((uintptr_t)(addr) + ((align) - 1) & ~((align) - 1))
#define ALIGN_ADDRESS(addr) ALIGN_ADDRESS_POW((addr), 16)

INLINE bool is_pow_of_2(uintptr_t addr);
INLINE size_t get_padding(uintptr_t addr);
INLINE void align_address(uintptr_t addr);
INLINE void arena_block_init(struct ArenaBlock *self, size_t capacity);
INLINE void arena_block_free( struct ArenaBlock *self);
INLINE void arena_init(struct Arena *self, size_t capacity);
INLINE void arena_free(struct Arena *self);
INLINE void arena_push_block(struct Arena *self, struct ArenaBlock *block);
INLINE const uint8_t *arena_unaligned_alloc(struct Arena *self);
INLINE const uint8_t *arena_alloc(struct Arena *self);