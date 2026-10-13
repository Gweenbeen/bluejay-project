// string.h - String API

#pragma once

#include "common.h"
#include <stdint.h>
#include <stddef.h>

// String :: Owning-string. Guaranteed to be null terminated
struct String
{
	const uint8_t *ptr;
	size_t length;
	size_t capacity;

	size_t begin;
	size_t end;
	size_t current;

	alignas(max_align_t) uint8_t inline_memory[8];
};

INLINE void string_init(struct String *self);
INLINE void string_free(struct String *self);

INLINE void string_reserve(struct String *self, size_t capacity);
INLINE void string_resize(struct String *self, size_t length);
INLINE void string_clear(struct String *self);

INLINE struct String string_from_cstring(const char *string);
INLINE struct String string_from_string_view(const struct StringView *string);
INLINE const uint8_t *string_to_cstring(const struct String *self);
INLINE struct StringView *string_to_string_view(const struct String *self);

INLINE void string_append(struct String *self, const char *string);
INLINE void string_append_string_view(struct String *self, struct StringView *string);

INLINE void string_concat(struct String *dest, struct String *src);
INLINE void string_concat_cstring(struct String *dest, const char *src);
INLINE void string_concat_string_view(struct String *dest, struct StringView *src);

INLINE struct String string_slice(struct String *self, size_t start, size_t end);
INLINE bool string_compare(struct String *dest, struct String *src);
INLINE bool string_equals(struct String *dest, struct String *src);
INLINE bool string_contains(struct String *self, char c);

size_t string_find(struct String *self, char c);