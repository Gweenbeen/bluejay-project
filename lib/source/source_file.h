// source_file.h - Source file

#pragma once

#include "common.h"
#include <stddef.h>

// SourceFile :: Source input
struct SourceFile
{
	const char *ptr;
	size_t length;
}; 

// SourceRange :: SourceFile range
struct SourceRange
{
	const char *ptr;
	size_t length;
};

// SourceFile :: Snapshot of SourceFile metadata
struct SourceView
{
	const char *ptr;
	size_t offset;
	size_t length;

	size_t line_start;
	size_t line_length;
	size_t column_start;
	size_t column_length;
};

// source_file_load :: Opens a path and reads contents into read only pointer
extern void source_file_load(struct SourceFile *self, const char *path);

// source_file_free :: Released SourceFile
extern void source_file_free(struct SourceFile *self);

// source_ptr :: Returns pointer in SourceFile
[[maybe_unused]] static const char *source_ptr(struct SourceFile *self)
{
	return (const char *)self->ptr;
}