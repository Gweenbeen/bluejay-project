// Copyright (c) 2026 Justin Wallace
// array.h - Dynamic contiguous array API

#pragma once

#include <stddef.h>

typedef struct Array
{
	void* data;
	size_t element_size;
	size_t length;
	size_t capacity;
} Array;

extern void array_init(Array* array, );
extern void array_free();
extern void array_push_back();
extern void array_pop();
extern void array_at();



typedef struct Entry
{

	void* value;
} Entry;