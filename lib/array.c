// array.c

#include "array.h"
#include "common.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// array_init :: Initializes an instance of Array
extern void array_init_impl(Array* array, size_t size, size_t capacity)
{
	array->size = size;
	array->capacity = capacity;

	array->length = 0;
	array->ptr = array->inline_memory;

	// Too large, alloc immediately
	if((array->size * array->capacity) > sizeof(array->inline_memory)) {
		array->ptr = (uint8_t*)malloc(array->size * array->capacity);
	}
}

// array_grow :: Grows Array
extern void array_grow_impl(Array* array, size_t new_capacity)
{
	if(array->ptr == array->inline_memory) {
		// Array.inline_memory is now unusable
		array->ptr = (uint8_t*)malloc(array->size * new_capacity);

		memcpy(array->ptr, array->inline_memory, array->size * array->length);
	} else {
		array->ptr = (uint8_t*)realloc(array->ptr, array->size * new_capacity);
	}

	array->capacity = new_capacity;
}

// array_at :: Returns a pointer to Array at index without bounds check
extern uint8_t* array_at_impl(Array* array, size_t index)
{
	return &(array->ptr[index * array->size]);
}

// array_free :: Releases an instance of Array
extern void array_free(Array* array)
{
	if(
		array->ptr != NULL &&
		array->ptr != array->inline_memory
	) {
		free(array->ptr);
	}

	array->ptr = NULL;
	array->size = 0;
	array->length = 0;
	array->capacity = 0;
}

// array_push_back :: Pushes an item to the back of Array
extern void array_push_back(Array* array, const uint8_t* restrict item)
{
	if(array->length == array->capacity) {
		array_grow(array);
	}

	uint8_t* next_slot = array_at_impl(array, array->length);
	memcpy(next_slot, item, array->size);

	array->length++;
}

// array_pop_back :: Pops an item from the back of Array, and returns a pointer
extern uint8_t* array_pop_back(Array* array)
{
	array->length = min_size(array->length + 1, 1);
	array->length--;

	return array_at(array, array->length);
}