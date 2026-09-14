// Copyright (c) 2026 Justin Wallace
// arena.h - Arena allocator with SBO

#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct ArenaBlock ArenaBlock;

typedef struct ArenaBlock
{
	size_t capacity;
	size_t used;

	void* memory;

	ArenaBlock* prev;
	ArenaBlock* next;
} ArenaBlock;

void arena_block_init(ArenaBlock* arena_block, size_t capacity);
void arena_block_free(ArenaBlock* arena_block);
void* arena_block_alloc(ArenaBlock* arena_block, size_t bytes);

typedef struct ArenaInline
{
	size_t capacity;
	size_t used;

	alignas(max_align_t) uint8_t memory[64];
} ArenaInline;

void* arena_inline_alloc(ArenaInline* arena_inline, size_t bytes);

// typedef struct Arena
// {
// 	size_t max_capacity;

// 	ArenaBlock* head;
// 	ArenaBlock* tail;
// } Arena;

// void arena_init(Arena* arena, size_t capacity);
// void arena_free(Arena* arena);
// void arena_alloc(Arena* arena, size_t size);
// void arena_reset(Arena* arena, size_t size);