// source_view - Non-owning view into contents of source

#pragma once

struct SourceFile;

struct SourceView
{
	struct SourceFile *source;

	size_t line_start;
	size_t line_length;

	size_t column_start;
	size_t column_length;
};