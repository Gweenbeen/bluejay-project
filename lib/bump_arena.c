// bump_arena.c - From 'bump_arena.h'

#include "bump_arena.h"
#include "common.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// above_capacity :: Returns true if BumpArenaBlock exceeds capacity
static bool above_capacity(struct BumpArenaBlock *self, size_t bytes);

extern struct BumpArenaBlock *bump_arena_block_make(size_t capacity)
{
	ASSERT(capacity != 0);

	struct BumpArenaBlock *block = malloc(sizeof(struct BumpArenaBlock));

	block->used = 0;
	block->capacity = capacity;
	block->ptr = malloc(block->capacity);
	block->next = nullptr;

	return block;
}

extern void bump_arena_block_free(struct BumpArenaBlock *self)
{
	ASSERT(self != nullptr);

	if (self->ptr != nullptr) {
		free((void *)self->ptr);
	}

	self->used = 0;
	self->capacity = 0;
}

extern void bump_arena_block_add(struct BumpArenaBlock *to, struct BumpArenaBlock *from)
{
	ASSERT(to != nullptr);
	ASSERT(from != nullptr);

	to->next = from;
}

extern void *bump_arena_block_alloc(struct BumpArenaBlock *self, size_t bytes)
{
	ASSERT(self != nullptr);
	ASSERT(bytes != 0);

	const uint8_t *ptr = &(self->ptr)[self->used];

	self->used += bytes;

	return (void *)ptr;
}

extern void bump_arena_init(struct BumpArena *self, size_t initial_capacity)
{
	ASSERT(self != nullptr);
	ASSERT(initial_capacity != 0);

	self->initial_capacity = initial_capacity;
	self->tail = nullptr;
	self->head = self->tail;
}

extern void bump_arena_free(struct BumpArena *self)
{
	ASSERT(self != nullptr);

	struct BumpArenaBlock *current = self->tail;

	while (current != nullptr) {
		struct BumpArenaBlock *next = current->next;

		bump_arena_block_free(current);

		free(current);

		current = next;
	}
}

extern void bump_arena_push_block(struct BumpArena *self)
{
	ASSERT(self != nullptr);

	struct BumpArenaBlock *block = bump_arena_block_make(self->head->capacity * 2);

	bump_arena_block_add(self->head, block);

	self->head = block;
}

extern void *bump_arena_alloc(struct BumpArena *self, size_t bytes)
{
	ASSERT(self != nullptr);
	ASSERT(bytes != 0);

	if (self->tail == nullptr) {
		self->tail = bump_arena_block_make(self->initial_capacity);
		self->head = self->tail;
	}

	if (above_capacity(self->head, bytes)) {
		bump_arena_push_block(self);
	}

	return bump_arena_block_alloc(self->head, bytes);
}

static bool above_capacity(struct BumpArenaBlock *self, size_t bytes)
{
	ASSERT(self != nullptr);
	ASSERT(bytes != 0);

	return ((self->used + bytes) > self->capacity);
}