// common.h

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INLINE [[gnu::always_inline]] static inline

// StringView :: Non-owning string with length. Not guaranteed to be null-terminated
struct StringView
{
	const uint8_t *ptr;
	size_t length;
};

// string_view_from_cstring :: Creates a StringView from a C-string
INLINE struct StringView string_view_from_cstring(const char *string, size_t length)
{
	return (struct StringView) {
		.ptr = (const uint8_t *)string,
		.length = length
	};
}

INLINE void swap(void *restrict a, void *restrict b, size_t length)
{
	uint8_t *da = (uint8_t *)a;
	uint8_t *db = (uint8_t *)b;

	for (size_t i = 0; i < length; i++) {
		uint8_t t = da[i];
		da[i] = db[i];
		db[i] = t;
	}
}

#define LOG_FATAL(msg, expr) \
 fprintf(\
 	stderr, \
 	"In %s:%d\n"\
 	"Statement: %s\n"\
 	"Error: %s\n"\
 	"Please send any bugs or reports to justin.wallace@gmail.com\n", \
 	__FILE__, __LINE__, #expr, #msg)

#define ASSERT(expr) do { if (!(expr)) LOG_FATAL("Expected TRUE", (expr)); } while (0)

[[noreturn]] void fatal(const char *msg)
{
	LOG_FATAL(msg, 0);
	exit(-1);
}

#ifdef NO_ASSERT
# define ASSERT(expr) 
#endif