// Copyright(c) 2026 Justin Wallace
// array.h - Array API template

#pragma once

#include "common.h"
#include <stdlib.h>

#define ARRAY_USING_SCRATCH

#ifndef ARRAY_INIT_SCRATCH_SIZE
#define ARRAY_INIT_SCRATCH_SIZE 8
#endif

#ifndef ARRAY_INIT_CAPACITY
#define ARRAY_INIT_CAPACITY 8
#endif

#ifndef ARRAY_LOAD_FACTOR
#define ARRAY_LOAD_FACTOR 2
#endif

#define ARRAY_INIT_IMPL(T__, struct__, capacity__)\
 struct__->length = 0;\
 struct__->capacity = capacity__;\
 struct__->ptr = malloc(sizeof(T__) * struct__->capacity);\

#define ARRAY_FREE_IMPL(struct__)\
 if(struct__->ptr != NULL) { free(struct__->ptr); }\
 struct__->length = 0;\
 struct__->capacity = 0;\
 struct__->ptr = NULL;\

#define ARRAY_AT_IMPL(struct__, index)\
 &struct__->ptr[index]\

#define ARRAY_BEGIN_IMPL(struct__) ARRAY_AT_IMPL(struct__, 0)
#define ARRAY_END_IMPL(struct__) ARRAY_AT_IMPL(struct__, struct__->length)

#define ARRAY_GROW_IMPL(T__, struct__)\
 struct__->ptr = realloc(struct__->ptr, sizeof(T__) * struct__->capacity * ARRAY_LOAD_FACTOR); \
 struct__->capacity *= ARRAY_LOAD_FACTOR; \

#define ARRAY_ALLOC_IMPL(T__, struct__, size__)
#define ARRAY_RESERVE_IMPL(T__, struct__, size__)
#define ARRAY_RESET_IMPL(T__, struct__)
#define ARRAY_FOR_EACH_IMPL(T__, struct__, type__)

#define DEFINE_ARRAY_STRUCT_IMPL(T__)\
 T__* ptr;\
 size_t length;\
 size_t capacity\

#define DEFINE_ARRAY_API_IMPL(T__, struct__, name__)\
 INLINE void name__##_init(struct__* arr) { ARRAY_INIT_IMPL(T__, arr, ARRAY_INIT_CAPACITY); }\
 INLINE void name__##_free(struct__* arr) { ARRAY_FREE_IMPL(arr); }\
 INLINE T__* name__##_at(struct__* arr, size_t index) { if(index >= arr->length) { return NULL; } return ARRAY_AT_IMPL(arr, index); }\
 INLINE T__* name__##_begin(struct__* arr) { return ARRAY_BEGIN_IMPL(arr); }\
 INLINE T__* name__##_end(struct__* arr) { return ARRAY_END_IMPL(arr); }\
 INLINE void name__##_push_back(struct__* arr, const T__* restrict item) { if(arr->length >= arr->capacity) { ARRAY_GROW_IMPL(T__, arr); } arr->ptr[arr->length++] = *item; }\
 INLINE T__* name__##_pop_back(struct__* arr) { if(arr->length == 0) { return ARRAY_AT_IMPL(arr, 0); } return ARRAY_AT_IMPL(arr, --arr->length); }\

#define DEFINE_ARRAY(T__, struct__, name__)\
 typedef struct struct__\
 {\
 	DEFINE_ARRAY_STRUCT_IMPL(T__);\
 } struct__;\
 DEFINE_ARRAY_API_IMPL(T__, struct__, name__);\

#define for_each(T__, iter__, begin__, end__) for(T__ iter__ = begin__; iter__ != end__; iter__++)

#define array_for_each(T__, iter__, obj__) for_each(T__, iter__, obj__.ptr, obj__.ptr + obj__.length)