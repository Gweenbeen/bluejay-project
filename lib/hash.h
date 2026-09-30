// hash.h

#pragma once

#include "common.h"

INLINE uint64_t hash_fnv1a_impl(const uint8_t* restrict ptr, size_t length, uint64_t seed0, uint64_t seed1)
{
	uint64_t hash = 14695981039346656037ULL;

	hash ^= seed0;
	hash ^= seed1;

	for(size_t i = 0; i < length; i++) {
		hash ^= ptr[i];
		hash *= 1099511628211ULL;
	}

	return (hash) ? hash : 1;
}

INLINE uint64_t hash_fnv1a_from_string_view(StringView* string_view)
{
	return hash_fnv1a_impl(string_view->ptr, string_view->length, 0, 0);
}

INLINE uint64_t hash_fnv1a_from_cstring(const char* string, size_t length)
{
	return hash_fnv1a_impl((uint8_t*)string, length, 0, 0);
}