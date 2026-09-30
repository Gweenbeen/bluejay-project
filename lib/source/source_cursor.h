// Copyright (c) 2026 Justin Wallace
// source_cursor - Moves between source file

#pragma once

#include "source_file.h"
#include "common.h"

// SourceCursor :: Cursor for SourceFile
typedef struct SourceCursor
{
	SourceFile* source_file;

	size_t current;
	size_t column;
	size_t line;

	size_t line_start;
	size_t line_end;
} SourceCursor;

// source_cursor_init :: Initializes an instance of SourceCursor
INLINE void source_cursor_init(SourceCursor* source_cursor, SourceFile* source_file)
{
	source_cursor->source_file = source_file;
}

// source_cursor_at :: Returns the character of SourceFile at index
INLINE const char source_cursor_at(SourceCursor* source_cursor, size_t index)
{
	return (const char)source_cursor->source_file->contents.ptr[index];
}

// source_cursor_current :: Returns the current character of SourceFile
INLINE const char source_cursor_current(SourceCursor* source_cursor)
{
	return source_cursor->source_file->contents.ptr[source_cursor->current];
}

// source_cursor_prev :: Returns the previous character of SourceFile
INLINE const char source_cursor_prev(SourceCursor* source_cursor)
{
	return source_cursor->source_file->contents.ptr[source_cursor->current - 1];
}

// source_cursor_peek :: Returns the following character of SourceFile
INLINE const char source_cursor_peek(SourceCursor* source_cursor)
{
	return source_cursor->source_file->contents.ptr[source_cursor->current + 1];
}

// source_cursor_advance :: Advances the cursor
INLINE void source_cursor_advance(SourceCursor* source_cursor)
{
	source_cursor->current++;
}

// source_cursor_is :: Returns true if the current character is the same as match
INLINE bool source_cursor_is(SourceCursor* source_cursor, const char match)
{
	return ((char)source_cursor->source_file->contents.ptr[source_cursor->current] == match);
}

// source_cursor_expect :: Returns true and increments the cursor if the current character is the 
//  same as match
INLINE bool source_cursor_expect(SourceCursor* source_cursor, const char match)
{
	if((char)source_cursor->source_file->contents.ptr[source_cursor->current] == match) {
		source_cursor->current++;
		return true;
	}

	return false;
}

// source_cursor_string :: Returns string pointer of SourceCursor
INLINE const uint8_t* source_cursor_string(SourceCursor* source_cursor)
{
	return source_cursor->source_file->contents.ptr;
}

// source_cursor_string :: Returns string pointer of SourceCursor at index
INLINE const uint8_t* source_cursor_string_at(SourceCursor* source_cursor, size_t index)
{
	return &(source_cursor->source_file->contents.ptr)[index];
}