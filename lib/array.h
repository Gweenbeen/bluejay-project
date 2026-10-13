// array.h - Template for typed dynamic array API

#pragma once

#include "common.h"


// DEFINE_ARRAY_STRUCT_IMPL :: Defines variables in struct to be used by dynamic array API
#define DEFINE_ARRAY_HEADER(type__) \
 type__ *ptr; \
 size_t length; \
 size_t capacity; \
 uint8_t inline_memory[8]

#define DEFINE_ARRAY_IMPL(array__, alias__, type__)\
 INLINE void alias__##_init(array__ *self);\
 INLINE void alias__##_free(array__ *self);\
 INLINE void alias__##_resize(array__ *self, size_t new_capacity);\
 INLINE void alias__##_reserve(array__ *self, size_t new_capacity);\
 INLINE void alias__##_place(array__ *self, type__ *item, size_t index);\
 INLINE type__ *alias__##_begin(array__ *self);\
 INLINE type__ *alias__##_end(array__ *self);\
 INLINE type__ *alias__##_at(array__ *self, size_t index);\
 INLINE const type__ *alias__##_begin_const(const array__ *self);\
 INLINE const type__ *alias__##_end_const(const array__ *self);\
 INLINE const type__ *alias__##_at_const(const array__ *self, size_t index);\
 INLINE void alias__##_clear(array__ *self);\
 INLINE void alias__##_push_back_ptr(array__ *self, type__ *item);\
 INLINE void alias__##_push_back(array__ *self, type__ item);\
 INLINE void alias__##_pop_back(array__ *self);\
 \
 INLINE void alias__##_init(array__ *self)\
 {\
 }\
 INLINE void alias__##_free(array__ *self)\
 {\
 }\
 \
 INLINE void alias__##_resize(array__ *self, size_t new_capacity)\
 {\
 }\
 \
 INLINE void alias__##_reserve(array__ *self, size_t new_capacity)\
 {\
 }\
 \
 INLINE void alias__##_place(array__ *self, type__ *item, size_t index)\
 {\
 }\
 INLINE type__ *alias__##_begin(array__ *self){ return self->ptr; }\
 INLINE type__ *alias__##_end(array__ *self) { return &(self->ptr)[self->length]; }\
 INLINE type__ *alias__##_at(array__ *self, size_t index) { return (index < self->length) ? &(self->ptr)[index] : nullptr; }\
 INLINE const type__ *alias__##_begin_const(const array__ *self) { return self->ptr;  }\
 INLINE const type__ *alias__##_end_const(const array__ *self) { return &(self->ptr)[self->length]; }\
 INLINE const type__ *alias__##_at_const(const array__ *self, size_t index) { return (index < self->length) ? &(self->ptr)[index] : nullptr; }\
 INLINE void alias__##_clear(array__ *self)\
 {\
 }\
 INLINE void alias__##_push_back_ptr(array__ *self, type__ *item)\
 {\
 }\
 INLINE void alias__##_push_back(array__ *self, type__ item)\
 {\
 }\
 INLINE void alias__##_pop_back(array__ *self)\
 {\
 }

// DEFINE_ARRAY_IMPL :: Defines functions for dynamic array usage 
// * array__ = Array struct
// * alias__ = Alternative variable name
// * type__ = Type
// INLINE void alias__##_init(array__ *self); 													
// INLINE void alias__##_free(array__ *self); 													
// [[deprecated]] INLINE void alias__##_resize(array__ *self, size_t new_length); 				
// INLINE void alias__##_reserve(array__ *self, size_t new_capacity); 							
// INLINE void alias__##_place(array__ *self, type__ *item, size_t index); 						
// INLINE type__ *alias__##_begin(array__ *self); 												
// INLINE type__ *alias__##_end(array__ *self); 													
// INLINE type__ *alias__##_at(array__ *self, size_t index); 										
// INLINE const type__ *alias__##_begin_const(const array__ *self); 								
// INLINE const type__ *alias__##_end_const(const array__ *self); 								
// INLINE const type__ *alias__##_at_const(const array__ *self, size_t index); 					
// INLINE void alias__##_clear(array__ *self); 													
// INLINE void alias__##_push_back_ptr(array__ *self, const type__ *item); 						
// INLINE void alias__##_push_back_ptr(array__ *self, type__ item); 								
// INLINE void alias__##_pop_back(array__ *self);


// Iterators for non-owning arrays
#define ARRAY_FOR_EACH(type__, iter__, array__) for (type__ iter__ = array__.ptr; iter__ != &(array__.ptr)[array__.length]; ++iter__)
#define ARRAY_FOR_EACH_CONST(type__, iter__, array__) for (const type__ iter__ = array__.ptr; iter__ != &(array__.ptr)[array__.length]; ++iter__)

// Iterators for owning arrays
#define ARRAY_PTR_FOR_EACH(type__, iter__, array__) for (type__ iter__ = array__->ptr; iter__ != &(array__->ptr)[array__->length]; ++iter__)
#define ARRAY_PTR_FOR_EACH_CONST(type__, iter__, array__) for (const type__ iter__ = array__->ptr; iter__ != &(array__->ptr)[array__->length]; ++iter__)