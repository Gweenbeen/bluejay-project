// source_file.c

#include "source_file.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

// source_file_read :: Reads file contents into SourceFile
extern void source_file_read(SourceFile* source_file, const char* path)
{
	FILE* f = fopen(path, "rb");

	fseek(f, 0, SEEK_END);
	size_t len = ftell(f);
	fseek(f, 0, SEEK_SET);

	// String is null-terminated
	char* src = (char*)malloc(len + 1);

	fread(src, 1, len, f);

	src[len] = '\0';

	source_file->contents = string_view_from_cstring(src, len);
	source_file->path = path;
	source_file->id = hash_fnv1a_from_cstring(path, strlen(path));
}

// source_file_read :: Releases SourceFile
extern void source_file_free(SourceFile* source_file)
{
	if(source_file->contents.ptr != NULL) {
		free((void*)source_file->contents.ptr);
	}

	source_file->contents.ptr = NULL;
	source_file->contents.length = 0;
}