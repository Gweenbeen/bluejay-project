// source_file.h

#pragma once

#include "common.h"

// SourceFile :: Source file to be used for compilation
typedef struct SourceFile
{
	const char* path;
	uint64_t id;
	StringView contents;
} SourceFile;

extern void source_file_read(SourceFile* source_file, const char* path);
extern void source_file_free(SourceFile* source_file);