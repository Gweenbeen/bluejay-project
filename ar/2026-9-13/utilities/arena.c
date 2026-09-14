// Copyright (c) 2026 Justin Wallace
// arena.c - From arena.h

#include "arena.h"
#include <stdint.h>
#include <stdlib.h>

void arena_block_init(ArenaBlock* arena_block, size_t capacity)
{
	arena_block->capacity = capacity;
	arena_block->used = 0;

	arena_block->memory = malloc(capacity);

	arena_block->prev = NULL;
	arena_block->next = NULL;
}

void arena_block_free(ArenaBlock* arena_block)
{
	if(arena_block->memory != NULL) {
		free(arena_block->memory);
	}

	arena_block->capacity = 0;
	arena_block->used = 0;
}
sdADWEA
void* arena_block_alloc(ArenaBlock* arena_block, size_t bytes)
{
	uint8_t* base_addr = (uint8_t*)arena_block->memory + arena_block->used;

	if(*base_addr > arena_block->capacity) {
		return NULL;
	}

	arena_block->used += bytes;

	return (void*)base_addr;
}

// arena_inline_alloc - Allocates an inline block of memory
void* arena_inline_alloc(ArenaInline* arena_inline, size_t bytes)
{
	uint8_t* base_addr = arena_inline->memory + arena_inline->used;

	if(*base_addr > arena_inline->capacity) {
		return NULL;
	}

	arena_inline->used += bytes;

	return (void*)new_addr;
}



typedef enum BucketState
{
	BUCKET_FREE = 0,
	BUCKET_TOMBSTONE = 1,
	BUCKET_OCCUPIED = 2,
}
typedef struct Bucket
{
	BucketState state;
	uint8_t hash;
	uint16_t distance_in_bucket;
} Bucket;

typedef struct Key
{
	StringView string;
} Key;

typedef struct Entry
{
	Bucket data;
	Key key;
	size_t num;
} Entry;

typedef struct Hashmap
{
	Entry* entries;
	size_t length;
	size_t capacity;

	uint64_t seed0;
	uint64_t seed1;

	alignas(max_align_t) uint8_t inlined[16554];
} Hashmap;