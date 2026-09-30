// common.h

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define INLINE [[gnu::always_inline]] static inline

// DEFINE_CLAMP :: Create typed clamp function
#define DEFINE_CLAMP(T, name) INLINE T clamp_##name(T n, T min, T max) { return (n > max) ? max : ((n < min) ? min : n); }

// DEFINE_MIN :: Create typed min function
#define DEFINE_MIN(T, name) INLINE T min_##name(T a, T b) { return (a < b) ? a : b; }

// DEFINE_MAX :: Create typed max function
#define DEFINE_MAX(T, name) INLINE T max_##name(T a, T b) { return (a > b) ? a : b; }

DEFINE_CLAMP(size_t, size);
DEFINE_MIN(size_t, size);
DEFINE_MAX(size_t, size);

#undef DEFINE_MAX
#undef DEFINE_MIN
#undef DEFINE_CLAMP

// Result :: Function return result
typedef enum Result
{
	RESULT_FAILURE = -1,

	RESULT_OK,
} Result;

// StringView :: Pointer and length
typedef struct StringView
{
	const uint8_t* ptr;
	size_t length;
} StringView;

INLINE StringView string_view_from_cstring(const char* string, size_t length)
{
	return (StringView){ .ptr = (uint8_t*)string, .length = length };
}

INLINE const uint8_t* string_view_to_cstring(StringView* string_view)
{
	return string_view->ptr;
}


#define FATAL(expr) fprintf(stdout, "!! Fatal error occured in %s:%d. \"%s\"", __FILE__, __LINE__, #expr)

#ifndef ENABLE_DEBUG
 #define ASSERT(expr) do { if(!(expr)) FATAL(expr); } while(0)
#else
 #define ASSERT(expr) do { } while(0)
#endif