// array_impl.h - 

#include "common.h"
#include <stddef.h>
#include <string.h>

struct Array
{
	int *ptr;
	size_t length;
	size_t capacity;
	alignas(max_align_t) uint8_t inline_memory[8];
};

INLINE bool array_init(struct Array *self);
INLINE void array_free(struct Array *self);
INLINE bool array_reserve(struct Array *self, size_t new_capacity);
INLINE void array_resize(struct Array *self, size_t new_length);
INLINE void array_place(struct Array *self, int *item, size_t index);
INLINE int *array_begin(struct Array *self);
INLINE int *array_end(struct Array *self);
INLINE int *array_at(struct Array *self, size_t index);
INLINE const int *array_begin_const(const struct Array *self);
INLINE const int *array_end_const(const struct Array *self);
INLINE const int *array_at_const(const struct Array *self, size_t index);
INLINE void array_clear(struct Array *self);
INLINE void array_push_back_obj(struct Array *self, int *item);
INLINE void array_push_back(struct Array *self, int item);
INLINE void array_pop_back(struct Array *self);

INLINE bool array_init(struct Array *self)
{
	ASSERT(self != nullptr);

	self->ptr = (int *)self->inline_memory;

	self->length = 0;
	self->capacity = sizeof(self->inline_memory) / sizeof(int);

	if (self->capacity == 0) {
		self->capacity = 4;

		self->ptr = malloc(self->capacity * sizeof(int));
		if (self->ptr == nullptr) {
			goto fail;
		}
	}

	return true;

fail:
	
	array_free(self);
	return false;
}

INLINE void array_free(struct Array *self)
{
	ASSERT(self != nullptr);

	if (self->ptr != nullptr && self->ptr != (int *)self->inline_memory) {
		free(self->ptr);
	}

	self->ptr = nullptr;
	self->length = 0;
	self->capacity = 0;
}

INLINE bool array_reserve(struct Array *self, size_t new_capacity)
{
	ASSERT(self != nullptr);

	if (new_capacity <= self->capacity) {
		return false;
	}

	if (self->ptr == (int *)self->inline_memory) {
		self->ptr = malloc(new_capacity * sizeof(int));

		memcpy(self->ptr, (int *)self->inline_memory, self->capacity * sizeof(int));
	} else {
		int *new_ptr = realloc(self->ptr, new_capacity * sizeof(int));

		if (new_ptr == nullptr) {
			free(new_ptr);
			goto fail;
		}
		self->ptr = new_ptr;
	}

	self->capacity = new_capacity;

	return true;

fail:

	array_free(self);
	return false;
}

INLINE void array_resize(struct Array *self, size_t new_length)
{
	ASSERT(self != nullptr);

	if (new_length > self->capacity) {
		array_reserve(self, new_length);	
	}

	self->length = new_length;

	return;

fail:
	
	array_free(self);
}

INLINE void array_place(struct Array *self, int *item, size_t index)
{
	ASSERT(self != nullptr);

	self->ptr[index] = *item;
}

INLINE int *array_begin(struct Array *self)
{
	ASSERT(self != nullptr);

	return self->ptr;
}

INLINE int *array_end(struct Array *self)
{
	ASSERT(self != nullptr);

	return &(self->ptr)[self->length];
}

INLINE int *array_at(struct Array *self, size_t index)
{
	ASSERT(self != nullptr);

	if (index >= self->length) {
		return nullptr;
	}

	return &(self->ptr)[index];
}

INLINE const int *array_begin_const(const struct Array *self)
{
	ASSERT(self != nullptr);

	return self->ptr;
}

INLINE const int *array_end_const(const struct Array *self)
{
	ASSERT(self != nullptr);

	return &(self->ptr)[self->length];
}

INLINE const int *array_at_const(const struct Array *self, size_t index)
{
	ASSERT(self != nullptr);

	if(index >= self->length) {
		return nullptr;
	}

	return &(self->ptr)[index];
}

INLINE void array_clear(struct Array *self)
{
	ASSERT(self != nullptr);

	self->length = 0;
}

INLINE void array_push_back_obj(struct Array *self, int *item)
{
	ASSERT(self != nullptr);

	if (item == nullptr) {
		return;
	}

	int new_item = *item;

	if (self->length >= self->capacity) {
		array_reserve(self, self->capacity * 2);
	}

	array_place(self, &new_item, self->length);
	++self->length;
}

INLINE void array_push_back(struct Array *self, int item)
{
	ASSERT(self != nullptr);

	array_push_back_obj(self, &item);
}

INLINE void array_pop_back(struct Array *self)
{
	ASSERT(self != nullptr);

	if (self->length == 0) {
		return;
	}

	--self->length;
}

#define FOR_EACH(T, i, arr) for (T i = array_begin(arr); i != array_end(arr); ++i)
#define FOR_EACH_CONST(T, i, arr) for (const T i = array_begin_const(arr); i != array_end_const(arr); ++i)

void test()
{
	struct Array arr = {0};
	array_init(&arr);

	array_push_back(&arr, 5);
	array_push_back(&arr, 10);
	array_push_back(&arr, 15);
	array_push_back(&arr, 20);
	array_push_back(&arr, 25);
	array_push_back(&arr, 30);
	array_push_back(&arr, 35);
	array_push_back(&arr, 40);
	array_push_back(&arr, 45);
	array_push_back(&arr, 50);

	FOR_EACH (int *, i, &arr) {
		*i += 5;
	}

	FOR_EACH_CONST (int *, i, &arr) {
		printf("number %d\n", *i);
	}

	array_free(&arr);
}