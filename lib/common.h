// common.h

#pragma once

#include <stdio.h>

#ifdef NOASSERT
# define ASSERT(expr) ((void *)0)
#else
# define ASSERT(expr) if (!(expr)) fprintf(stderr, "Failed: %s in file %s:%d\n", #expr, __FILE__, __LINE__)
#endif