// common.h

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

struct StringView
{
	const uint8_t *ptr;
	size_t length;
};

static inline struct StringView string_view_make(const uint8_t *ptr, size_t length)
{
	return (struct StringView) {
		.ptr = ptr,
		.length = length,
	};
}


#ifdef NOASSERT
# define ASSERT(expr) ((void *)0)
#else
# define ASSERT(expr) if (!(expr)) fprintf(stderr, "Failed: %s in file %s:%d\n", #expr, __FILE__, __LINE__)
#endif