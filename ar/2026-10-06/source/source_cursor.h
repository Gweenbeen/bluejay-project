// Copyright (c) 2026 Justin Wallace
// self - Moves between source file

#pragma once

#include "source_file.h"
#include "common.h"

// SourceCursor :: Cursor for SourceFile
typedef struct SourceCursor
{
	struct SourceFile* source_file;

	size_t current;
	size_t column;
	size_t line;

	size_t line_start;
	size_t line_end;
} SourceCursor;

// source_cursor_init :: Initializes an instance of SourceCursor
STATIC void source_cursor_init(SourceCursor* self, struct SourceFile* source_file)
{
	self->source_file = source_file;
}

// source_cursor_at :: Returns the character of SourceFile at index
STATIC const char source_cursor_at(SourceCursor* self, size_t index)
{
	return (const char)self->source_file->contents.ptr[index];
}

// source_cursor_current :: Returns the current character of SourceFile
STATIC const char source_cursor_current(SourceCursor* self)
{
	return self->source_file->contents.ptr[self->current];
}

// source_cursor_prev :: Returns the previous character of SourceFile
STATIC const char source_cursor_prev(SourceCursor* self)
{
	return self->source_file->contents.ptr[self->current - 1];
}

// source_cursor_peek :: Returns the following character of SourceFile
STATIC const char source_cursor_peek(SourceCursor* self)
{
	return self->source_file->contents.ptr[self->current + 1];
}

// source_cursor_advance :: Advances the cursor
STATIC void source_cursor_advance(SourceCursor* self)
{
	self->current++;
}

// source_cursor_is :: Returns true if the current character is the same as match
STATIC bool source_cursor_is(SourceCursor* self, const char match)
{
	return ((char)self->source_file->contents.ptr[self->current] == match);
}

// source_cursor_expect :: Returns true and increments the cursor if the current character is the 
//  same as match
STATIC bool source_cursor_expect(SourceCursor* self, const char match)
{
	if((char)self->source_file->contents.ptr[self->current] == match) {
		self->current++;
		return true;
	}

	return false;
}

// source_cursor_string :: Returns string pointer of SourceCursor
STATIC const uint8_t* source_cursor_string(SourceCursor* self)
{
	return self->source_file->contents.ptr;
}

// source_cursor_string :: Returns string pointer of SourceCursor at index
STATIC const uint8_t* source_cursor_string_at(SourceCursor* self, size_t index)
{
	return &(self->source_file->contents.ptr)[index];
}