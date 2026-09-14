// Copyright (c) 2026 Justin Wallace
// bjcc.c - Project entry point

// #include "utilities/arena.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StringView
{
	const char* string;
	size_t length;
} StringView;

static const char* string_view_to_cstring(StringView* string_view) { return string_view->string; }

static StringView string_view_from_cstring(const char* string) { return (StringView){ string, strlen(string) }; }

int main(int argc, const char* argv[])
{
	const char str[] = "Hello, world!\n";
	StringView string = string_view_from_cstring(str);

	printf("%s\n", string_view_to_cstring(&string));
	return 0;
}

// return_1 :: returns a 1
int return_1(void) { return 1; }