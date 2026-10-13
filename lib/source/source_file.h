// source_file.h

#pragma once

#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// SourceFile :: File contents
struct SourceFile
{
	const char *path;
	uint64_t id;

	struct StringView contents;
};

// source_file_load :: Reads path contents into a null-terminated string
INLINE void source_file_load(struct SourceFile *self, const char *path)
{
	FILE *f = fopen(path, "rb");

	fseek(f, 0, SEEK_END);
	size_t length = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *read = malloc(length + 1);
	fread(read, 1, length, f);

	read[length] = '\0';

	self->contents = string_view_from_cstring(read, length);
	self->path = path;
	self->id = fileno(f);

	fclose(f);
}

// source_file_free :: Releases an instance of SourceFile
INLINE void source_file_free(struct SourceFile *self)
{
	if (self->contents.ptr != NULL) {
		free((void *)self->contents.ptr);
	}

	self->contents.ptr = NULL;
	self->contents.length = 0;
}