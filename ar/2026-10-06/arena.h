// vmem.h

#pragma once

#include <stdint.h>

// ArenaPage :: A single doubly-linked block of memory
struct ArenaPage
{
	const uint8_t* ptr;

	size_t used;
	size_t capacity;

	struct ArenaPage* prev;
	struct ArenaPage* next;
};

// Arena :: Header that defines a reigon of memory to be used by a process
struct Arena
{
	struct ArenaPage* head;
	struct ArenaPage* tail;
	struct ArenaPage* current;

	alignas(max_align_t) uint8_t inline_memory[8];
};

void arena_page_init(struct ArenaPage* self)
{
	self->ptr = NULL;
	self->used = 0;
	self->capacity = 128;
	self->prev = NULL;
	self->next = NULL;
}

void arena_page_free(struct ArenaPage* self)
{
	if(self->ptr != NULL) {
		free(self->ptr);
	}

	self->used = 0;
	self->capacity = 0;
	self->prev = NULL;
	self->next = NULL;
}

void arena_init(struct Arena* self)
{
	self->head = NULL;
	self->tail = NULL;
	self->current = self->head;
}

void arena_free(struct Arena* self)
{
	struct ArenaPage* current = self->head;
	while(current != NULL) {
		struct ArenaPage* next = current->prev;

		arena_page_free(current);
		free(current);

		current = self->head;
	}
}

void arena_push(struct Arena* self)
{
	struct ArenaPage* new_page = malloc(sizeof(ArenaPage));
	arena_page_init(new_page);

	self->head->prev = self->head;
	new_page->prev = self->head;
	self->head = new_page;

}

void arena_pop(struct Arena* self);

const uint8_t* restrict arena_alloc(struct Arena* self)
{
	//
}