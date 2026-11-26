// source_cursor.h - 

#pragma once

#include "source/source_file.h"
#include <stddef.h>

// SourceCursor :: Tracks position in SourceCursor
struct SourceCursor
{
	// const char *ptr;
	// size_t length;
	struct SourceFile *source;
	size_t current;
	size_t column;
	size_t line;
};

// source_cursor_make :: Creates a struct SourceCursor
static struct SourceCursor source_cursor_make(struct SourceFile *source);

// source_cursor_current :: Returns the current character in SourceCursor
static char source_cursor_current(struct SourceCursor *self);

// source_cursor_peek :: Returns the character ahead of the current in SourceCursor
static char source_cursor_peek(struct SourceCursor *self);

// source_cursor_prev :: Returns the character behind the current in SourceCursor
static char source_cursor_prev(struct SourceCursor *self);

// source_cursor_advance :: Advances the cursor in SourceCursor
static void source_cursor_advance(struct SourceCursor *self);

// source_cursor_rewind :: Rewinds the cursor in SourceCursor
static void source_cursor_rewind(struct SourceCursor *self);

// source_cursor_is :: Returns true if the current character in SourceCursor is 'c'
static bool source_cursor_is(struct SourceCursor *self, char c);

// source_cursor_expect :: Returns true if the current character in SourceCursor is 'c' and 
// advances by one
static bool source_cursor_expect(struct SourceCursor *self, char c);

// source_cursor_ptr :: Returns the pointer to the original source text in SourceCursor
[[maybe_unused]] static const char *source_cursor_ptr(struct SourceCursor *self);

static struct SourceCursor source_cursor_make(struct SourceFile *source)
{
	return (struct SourceCursor){
		.source = source,
		.current = 0,
		.column = 0,
		.line = 1,
	};
}

static char source_cursor_current(struct SourceCursor *self)
{
	return self->source->ptr[self->current];
}

static char source_cursor_peek(struct SourceCursor *self)
{
	if ((self->current + 1) > self->source->length) {
		return self->source->ptr[self->current];
	}
	return self->source->ptr[self->current + 1];
}

static char source_cursor_prev(struct SourceCursor *self)
{
	if ((self->current - 1) < 0) {
		return self->source->ptr[self->current];
	}
	return self->source->ptr[self->current - 1];
}

static void source_cursor_advance(struct SourceCursor *self)
{
	if ((self->current + 1) <= self->source->length + 1) {
		++self->current;
		++self->column;
	}

	if (self->source->ptr[self->current] == '\n') {
		self->column = 0;
		++self->line;
	}
}

static void source_cursor_rewind(struct SourceCursor *self)
{
	if ((self->current + 1) >= 0) {
		--self->current;
	}
}

static bool source_cursor_is(struct SourceCursor *self, char c)
{
	if (self->source->ptr[self->current] == c) {
		return true;
	}
	return false;
}

static bool source_cursor_expect(struct SourceCursor *self, char c)
{
	if (self->source->ptr[self->current] == c) {
		++self->current;
		return true;
	}
	return false;
}

[[maybe_unused]] static const char *source_cursor_ptr(struct SourceCursor *self)
{
	return (const char *)self->source->ptr;
}


[[maybe_unused]] static struct SourceView source_view_make(struct SourceCursor *cursor, size_t start)
{
	return (struct SourceView){
		.ptr = cursor->source->ptr ,
		.offset = start,
		.length = cursor->current - start,
		.line_start = 0,
		.line_length = 0,
		.column_start = 0,
		.column_length = 0,
	};
}