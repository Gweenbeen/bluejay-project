// source_file.h

#pragma once

#include "common.h"
#include <stddef.h>

typedef struct SourceFile SourceFile;

// SourceView :: Metadata taken from a SourceFile
typedef struct SourceView
{
	SourceFile* source_file;

	size_t start;
	size_t length;
	size_t line_start;
	size_t line_length;

	size_t line;
	size_t column;
} SourceView;

#define NO_SOURCE_VIEW (SourceView){0}

INLINE SourceView source_view_from_source(SourceFile* source_file) { return (SourceView){0}; }