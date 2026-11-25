// array.h

#pragma once

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

struct IntArray
{
	int *ptr;
	size_t length;
	size_t capacity;
	alignas(max_align_t) uint8_t buf[sizeof(int) * 2];
};

[[deprecated]] static bool int_array_init(struct IntArray *self)
{
	ASSERT(self);

	self->length = 0;
	self->capacity = 4;

	self->ptr = malloc(sizeof(int) * self->capacity);

	if (self->ptr != nullptr) {
		return false;
	}

	return true;
}

[[deprecated]] static void int_array_free(struct IntArray *self)
{
	ASSERT(self);

	if (self->ptr != nullptr) {
		free(self->ptr);
	}

	self->ptr = nullptr;
	self->length = 0;
	self->capacity = 0;	
}

[[deprecated]] static bool int_array_reserve(struct IntArray *self, size_t new_capacity)
{
	ASSERT(self);
	ASSERT(new_capacity != 0);

	int *new_ptr = realloc(self->ptr, sizeof(int) * (self->capacity + new_capacity));

	if (new_ptr == nullptr) {
		return false;
	}
	self->ptr = new_ptr;
	
	self->capacity += new_capacity;

	return true;
}

[[deprecated]] static void int_array_clear(struct IntArray *self)
{
	ASSERT(self);

	self->length = 0;
}

[[deprecated]] static void int_array_place(struct IntArray *self, size_t index, int *item)
{
	ASSERT(self);

	self->ptr[index] = *item;
}

[[deprecated]] static int *int_array_push_back_ptr(struct IntArray *self, int *item)
{
	ASSERT(self != nullptr);
	ASSERT(item != nullptr);

	// Undefined behavior if array pointer is passed as an argument; must redeclare as local 
	// variable, before potential realloc
	int nitem = *item; 

	if (self->length >= self->capacity) {
		if (!int_array_reserve(self, self->capacity)) {
			return nullptr;
		}
	}

	int_array_place(self, self->length, &nitem);
	++self->length;

	return &(self->ptr[self->length]);
}

[[deprecated]] static int *int_array_push_back(struct IntArray *self, int item)
{
	ASSERT(self != nullptr);

	return int_array_push_back_ptr(self, &item);
}

[[deprecated]] static void int_array_pop_back(struct IntArray *self)
{
	ASSERT(self);

	if (self->length > 0) {
		--self->length;
	}
}

[[deprecated]] static int *int_array_begin(struct IntArray *self)
{
	ASSERT(self);

	return self->ptr;
}

[[deprecated]] static int *int_array_end(struct IntArray *self)
{
	ASSERT(self);

	return &(self->ptr[self->length]);
}

[[deprecated]] static int *int_array_at(struct IntArray *self, size_t index)
{
	ASSERT(self);

	return &(self->ptr[index]);
}

[[deprecated]] static const int *int_array_const_begin(struct IntArray *self)
{
	ASSERT(self);

	return (const int *)self->ptr;
}

[[deprecated]] static const int *int_array_const_end(struct IntArray *self)
{
	ASSERT(self);

	return (const int *)&(self->ptr[self->length]);
}

[[deprecated]] static const int *int_array_const_at(struct IntArray *self, size_t index)
{
	ASSERT(self);

	return (const int *)&(self->ptr[index]);
}

#define ARRAY_FOR_EACH(type, iter, arr) for (type iter = arr.ptr; iter != &(arr.ptr[arr.length]); ++iter)

#define ARRAY_FOR_EACH_PTR(type, iter, arr) for (type iter = arr->ptr, iter != &(arr->ptr[arr->length]); ++iter)