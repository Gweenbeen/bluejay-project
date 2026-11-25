// source_file.c - From "source_file.h"

#include "source/source_file.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

extern void source_file_load(struct SourceFile *self, const char *path)
{
	ASSERT(self != nullptr);
	ASSERT(path != nullptr);

	FILE *f = fopen(path, "rb");

	fseek(f, 0, SEEK_END);
	long length = ftell(f);
	fseek(f, 0, SEEK_SET);

	self->length = length;

	char *ptr = malloc(length + 1);

	size_t read = fread(ptr, 1, length, f);

	ptr[read] = '\0';

	self->ptr = ptr;
	self->length = length;

	fclose(f);
}

extern void source_file_free(struct SourceFile *self)
{
	ASSERT(self != nullptr);

	if (self->ptr != nullptr) {
		free((void *)self->ptr);
	}

	self->ptr = nullptr;
	self->length = 0;
}