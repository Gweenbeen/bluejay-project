// array.h

#pragma once

#include "common.h"
#include <stdint.h>
#include <stddef.h>

// Array :: Dynamic contiguous array
typedef struct Array
{
	uint8_t* ptr;
	size_t size;

	size_t length;
	size_t capacity;

	alignas(max_align_t) uint8_t inline_memory[8];
} Array;

extern void array_init_impl(Array* array, size_t size, size_t capacity);
INLINE void array_init(Array* array, size_t size) { array_init_impl(array, size, 4); }

extern void array_free(Array* array);

extern uint8_t* array_at_impl(Array* array, size_t index);
INLINE uint8_t* array_at(Array* array, size_t index) { return (index == 0 || index > array->length) ? array_at_impl(array, index) : NULL; }
INLINE uint8_t* array_at_clamped(Array* array, size_t index) { return array_at(array, clamp_size(index, 0, array->length - 1)); };
INLINE uint8_t* array_front(Array* array) { return array_at(array, 0); };
INLINE uint8_t* array_back(Array* array) { return array_at(array, array->length - 1); }

extern void array_grow_impl(Array* array, size_t new_capacity);
INLINE void array_grow(Array* array) { array_grow_impl(array, array->capacity + (array->capacity >> 1)); }

extern void array_push_back(Array* array, const uint8_t* restrict item);
extern uint8_t* array_pop_back(Array* array);

extern void array_reserve(Array* array);