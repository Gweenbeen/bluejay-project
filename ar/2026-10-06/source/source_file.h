// source_file.h

#pragma once

#include "common.h"

// SourceFile :: Source file to be used for compilation
struct SourceFile
{
	const char* path;
	uint64_t id;
	
	struct StringView contents;
};

extern void source_file_read(struct SourceFile* self, const char* path);
extern void source_file_free(struct SourceFile* self);