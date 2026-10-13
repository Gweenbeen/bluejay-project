// source_file.c

#include "source_file.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

// source_file_read :: Reads file contents into SourceFile
extern void source_file_read(struct SourceFile* self, const char* path)
{
	FILE* f = fopen(path, "rb");

	fseek(f, 0, SEEK_END);
	size_t len = ftell(f);
	fseek(f, 0, SEEK_SET);

	// String is null-terminated
	char* src = (char*)malloc(len + 1);

	fread(src, 1, len, f);

	src[len] = '\0';

	self->contents = string_view_from_cstring_l(src, len);
	self->path = path;
	self->id = hash_fnv1a_from_cstring(path, strlen(path));
}

// source_file_read :: Releases SourceFile
extern void source_file_free(struct SourceFile* self)
{
	if(self->contents.ptr != NULL) {
		free((void*)self->contents.ptr);
	}

	self->contents.ptr = NULL;
	self->contents.length = 0;
}