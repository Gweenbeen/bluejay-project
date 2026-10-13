// output.h

#pragma once

// EmitterContext :: Manages code generation and formatting
struct EmitterContext
{
	FILE *handle;
	const char *path;
};

INLINE VOID emitter_context_init();


// output_emit :: Emits a file
INLINE void output_emit(FILE *file, struct SourceFile *source_file)
{
	for(size_t i = 0; i < source_file->contents.length; i++) {
		char string[9] = "char: ";
		const char end[] = {
			(char)source_file->contents.ptr[i],
			'\n',
		};

		strncat(string, end, sizeof(string) - strlen(string) - 1);

		fwrite(string, strlen(string), 1, file);

	}

	fwrite("\n", 1, 1, file);
}