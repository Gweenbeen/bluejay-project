// bump_arena.h - Untyped bump allocator API

#pragma once

#include "common.h"
#include <stdint.h>
#include <stddef.h>

// BumpArenaBlock :: Linked arena node
struct BumpArenaBlock
{
	const uint8_t *ptr;
	size_t used;
	size_t capacity;

	struct BumpArenaBlock *next;
};

// BumpArena :: BumpArena header
struct BumpArena
{
	size_t initial_capacity;
	struct BumpArenaBlock *tail; // first
	struct BumpArenaBlock *head; // current
};

// bump_arena_block_make :: Initializes an BumpArenaBlock node
extern struct BumpArenaBlock *bump_arena_block_make(size_t capacity);

// bump_arena_block_free :: Releases an BumpArenaBlock node
extern void bump_arena_block_free(struct BumpArenaBlock *self);

// bump_arena_block_add :: Adds 'from' to the next pointer of 'to' in an BumpArenaBlock
extern void bump_arena_block_add(struct BumpArenaBlock *to, struct BumpArenaBlock *from);

// bump_arena_block_alloc :: Returns bytes from an BumpArenaBlock 
extern void *bump_arena_block_alloc(struct BumpArenaBlock *self, size_t bytes);

// bump_arena_init :: Initializes an instance of BumpArena
extern void bump_arena_init(struct BumpArena *self, size_t initial_capacity);

// bump_arena_free :: Releases an instance of BumpArena
extern void bump_arena_free(struct BumpArena *self);

// bump_arena_push_block :: Pushes a new BumpArenaBlock onto BumpArena
extern void bump_arena_push_block(struct BumpArena *self);

// bump_arena_alloc :: Returns bytes from the current BumpArenaBlock
extern void *bump_arena_alloc(struct BumpArena *self, size_t bytes);