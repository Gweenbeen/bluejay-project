// array.h

#pragma once

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

constexpr size_t ARRAY_MAX_BUFFER_SIZE = 0;

#define DEFINE_ARRAY_HEADER(type__) \
 type__ *ptr; \
 size_t length; \
 size_t capacity; \
 alignas(max_align_t) type__ buf[ARRAY_MAX_BUFFER_SIZE]

#define DEFINE_ARRAY_IMPL(struct__, alias__, type__)                                  			\
 static bool alias__##_init(struct__ *self);                                          			\
 static void alias__##_free(struct__ *self);                                          			\
 static bool alias__##_reserve(struct__ *self, size_t new_capacity);                  			\
 static void alias__##_clear(struct__ *self);                                         			\
 static void alias__##_place(struct__ *self, size_t index, type__ *item);             			\
 static type__ *alias__##_push_back_ptr(struct__ *self, type__ *item);                			\
 static type__ *alias__##_push_back(struct__ *self, type__ item);                        		\
 static void alias__##_pop_back(struct__ *self);                                      			\
 static type__ *alias__##_begin(struct__ *self);                                      			\
 static type__ *alias__##_end(struct__ *self);                                        			\
 static type__ *alias__##_at(struct__ *self, size_t index);                           			\
 static const type__ *alias__##_const_begin(const struct__ *self);                          			\
 static const type__ *alias__##_const_end(const struct__ *self);                            			\
 static const type__ *alias__##_const_at(const struct__ *self, size_t index);               			\
																					  			\
 static bool alias__##_init(struct__ *self)                                           			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                                    \
																					  			\
	self->length = 0;                                                                 			\
	self->capacity = 4;                                                               			\
																					  			\
	self->ptr = malloc(sizeof(type__) * self->capacity);                                 		\
																					  			\
	if (self->ptr == nullptr) {                                                       			\
		return false;                                                                 			\
	}                                                                                 			\
																					  			\
	return true;                                                                      			\
 }                                                                                    			\
																					  			\
 static void alias__##_free(struct__ *self)                                           			\
 {                                                                                    			\
	ASSERT(self != nullptr); 	                                                      			\
																					  			\
	if (self->ptr != nullptr) {                                                       			\
		free(self->ptr);                                                              			\
	}                                                                                 			\
																					  			\
	self->ptr = nullptr;                                                              			\
	self->length = 0;                                                                 			\
	self->capacity = 0;                                                               			\
 }                                                                                    			\
																					  			\
 static bool alias__##_reserve(struct__ *self, size_t new_capacity)                   			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                                    \
	ASSERT(new_capacity != 0);                                                        			\
																					  			\
	if (new_capacity <= self->capacity) { 														\
		return true; 																			\
	} 																							\
																								\
	type__ *new_ptr = realloc(self->ptr, sizeof(type__) * new_capacity);						\
																					  			\
	if (new_ptr == nullptr) {                                                          			\
		return false;                                                                 			\
	}                                                                                 			\
	self->ptr = new_ptr;                                                              			\
																					  			\
	self->capacity = new_capacity;                                                   			\
																					  			\
	return true;                                                                      			\
 }                                                                                    			\
																					  			\
 static void alias__##_clear(struct__ *self)                                          			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                                    \
																					  			\
	self->length = 0;                                                                 			\
 }                                                                                    			\
																					  			\
 static void alias__##_place(struct__ *self, size_t index, type__ *item)              			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                                    \
																					  			\
	self->ptr[index] = *item;                                                         			\
 }                                                                                    			\
																					  			\
 static type__ *alias__##_push_back_ptr(struct__ *self, type__ *item)                 			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                          			\
	ASSERT(item != nullptr);                                                          			\
																								\
	type__ nitem = *item;                                                                		\
																					  			\
	if (self->length >= self->capacity) {                                             			\
		if (!alias__##_reserve(self, self->capacity * 2)) {                                		\
			return nullptr;                                                           			\
		}                                                                             			\
	}                                                                                 			\
																					  			\
	alias__##_place(self, self->length, &nitem);                                      			\
	++self->length;                                                                   			\
																					  			\
	return &(self->ptr[self->length - 1]);                                                		\
 }                                                                                    			\
																					  			\
 static type__ *alias__##_push_back(struct__ *self, type__ item)                         		\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                          			\
																					  			\
	return alias__##_push_back_ptr(self, &item);                                      			\
 }                                                                                    			\
																					  			\
 static void alias__##_pop_back(struct__ *self)                                       			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                           			\
																					  			\
	if (self->length > 0) {                                                           			\
		--self->length;                                                               			\
	}                                                                                 			\
 }                                                                                    			\
																					  			\
 static type__ *alias__##_begin(struct__ *self)                                       			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                           			\
																					  			\
	return self->ptr;                                                                 			\
 }                                                                                    			\
																					  			\
 static type__ *alias__##_end(struct__ *self)                                         			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                           			\
																					  			\
	return &(self->ptr[self->length]);                                                			\
 }                                                                                    			\
																					  			\
 static type__ *alias__##_at(struct__ *self, size_t index)                            			\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                           			\
																					  			\
	return &(self->ptr[index]);                                                       			\
 }                                                                                    			\
																					  			\
 static const type__ *alias__##_const_begin(const struct__ *self)                           	\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                           			\
																					  			\
	return (const type__ *)self->ptr;                                                 			\
 }                                                                                    			\
																					  			\
 static const type__ *alias__##_const_end(const struct__ *self)                             	\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                           			\
																					  			\
	return (const type__ *)&(self->ptr[self->length]);                                			\
 }                                                                                    			\
																					  			\
 static const type__ *alias__##_const_at(const struct__ *self, size_t index)                	\
 {                                                                                    			\
	ASSERT(self != nullptr);                                                           			\
																					  			\
	return (const type__ *)&(self->ptr[index]);                                       			\
} 

#define ARRAY_FOR_EACH(type, iter, arr) \
 for (type iter = arr.ptr; iter != &(arr.ptr[arr.length]); ++iter)

#define ARRAY_FOR_EACH_PTR(type, iter, arr) \
 for (type iter = arr->ptr; iter != &(arr->ptr[arr->length]); ++iter)