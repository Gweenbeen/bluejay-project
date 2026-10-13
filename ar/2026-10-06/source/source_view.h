// source_file.h

#pragma once

#include "common.h"
#include <stddef.h>


// SourceView :: Metadata taken from a SourceFile
struct SourceView
{
	struct SourceFile* source_file;

	size_t start;
	size_t length;
	size_t line_start;
	size_t line_length;

	size_t line;
	size_t column;
};

#define NO_SOURCE_VIEW (struct SourceView){0}

INLINE SourceView source_view_from_source(struct SourceFile* self) { return (struct SourceView){0}; }