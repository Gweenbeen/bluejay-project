// Copyright (c) 2026 Justin Wallace
// bjcc.c - Compiler

#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct StringView
{
	const uint8_t* ptr;
	size_t length;
} StringView;

StringView string_view_from_cstring(const char* string)
{
	return (StringView){ .ptr = string, .length = strlen(string) };
}

int main(int argc, const char* argv[])
{
	printf("Hello, world!\n");

	printf("%s", argv[1]);
	return 0;
}