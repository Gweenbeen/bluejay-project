// Copyright (c) 2026 Justin Wallace
// lexer.c - Lexical analysis

#include "lexer.h"
#include "token.h"
#include "common.h"
#include <ctype.h>

static const char keywords[];
static int keyword_exists(const char* start, size_t length);
INLINE Token next_token(Lexer* self);
INLINE Token next_symbol_or_operator(Lexer* self);
INLINE Token next_keyword_or_identifier(Lexer* self);
INLINE Token next_string_literal(Lexer* self);
INLINE Token next_numeric_literal(Lexer* self);

// next_keyword :: Tokenizes all characters in SourceFile
extern void lexer_tokenize(Lexer* self, struct SourceFile* source_file, TokenStream* token_stream)
{
	self->source_file = source_file;
	self->tokens = token_stream;

	source_cursor_init(&self->cursor, self->source_file);
	
	for(;;) {
		Token t = next_token(self);

		token_stream_push_back(self->tokens, &t);

		if(t.kind == TOKEN_EOF) {
			break;
		}
	}

	for(size_t i = 0; i < self->tokens->length; i++) {
		Token* t = token_stream_at(self->tokens, i);
		printf("token %02d: %.*s \n", t->kind, (int)t->source.length, t->source.ptr);
	}

	// array_for_each(Token*, t, self->tokens) {
	// 	printf("token: %.*s %d\n", t->source.length, t->source.ptr, t->kind);
	// }
}


// skip_whitespace :: Advances cursor until non-whitespace character is reached
INLINE void skip_whitespace(Lexer* self)
{
	while(isspace(source_cursor_current(&self->cursor)) || source_cursor_is(&self->cursor, '\t')) {
		source_cursor_advance(&self->cursor);
	}
}

// make_token :: Token creation helper
INLINE Token make_token(Lexer* self, TokenKind kind, size_t start)
{
	Token tok = {0};
	tok.kind = kind;
	tok.source.ptr = source_cursor_string_at(&self->cursor, start);
	tok.source.length = self->cursor.current - start;

	return tok;
}

// next_keyword :: Returns the next token
INLINE Token next_token(Lexer* self)
{
	skip_whitespace(self);

	Token tok = {0};

	// Keyword or identifier
	if(isalpha(source_cursor_current(&self->cursor))) {
		tok = next_keyword_or_identifier(self);
		goto end;
	}

	// String literal
	if(source_cursor_is(&self->cursor, '\"')) {
		tok = next_symbol_or_operator(self);
		goto end;
	}

	// Numeric literal
	if(isdigit(source_cursor_current(&self->cursor))) {
		tok = next_symbol_or_operator(self);
		goto end;
	}

	// EOF token
	if(source_cursor_is(&self->cursor, '\0')) {
		tok = next_symbol_or_operator(self);
		goto end;
	}

	// Fall back to symbol or operator, or error token
	tok = next_symbol_or_operator(self);

end:

	return tok;
}

// next_symbol_or_operator :: Returns the next symbol or operator token
INLINE Token next_symbol_or_operator(Lexer* self)
{
	TokenKind kind = TOKEN_UNKNOWN;
	size_t start = self->cursor.current;

	source_cursor_advance(&self->cursor);

	if(source_cursor_is(&self->cursor, '\0')) {
		kind = TOKEN_EOF;
	}

	return make_token(self, kind, start);
}

// next_keyword :: Returns the next keyword or identifier token
INLINE Token next_keyword_or_identifier(Lexer* self)
{
	TokenKind kind = TOKEN_IDENTIFIER;
	size_t start = self->cursor.current;

	while(isalnum(source_cursor_current(&self->cursor)) || source_cursor_is(&self->cursor, '_')) {
		source_cursor_advance(&self->cursor);
	}

	int kw = keyword_exists((const char*)source_cursor_string_at(&self->cursor, start), self->cursor.current - start);

	if(kw != -1) {
		kind = kw;
	}

	return make_token(self, kind, start);
}

// next_string_literal :: Returns the next string literal token
INLINE Token next_string_literal(Lexer* self)
{
	TokenKind kind = TOKEN_UNKNOWN;

	// Consume first '"'
	source_cursor_advance(&self->cursor);

	size_t start = self->cursor.current;

	while(!source_cursor_is(&self->cursor, '\"')) {
		source_cursor_advance(&self->cursor);
	}

	Token tok =  make_token(self, kind, start);

	// Consume last '"'
	source_cursor_advance(&self->cursor);

	return tok;
}

// next_string_literal :: Returns the next numeric literal token
INLINE Token next_numeric_literal(Lexer* self)
{
	TokenKind kind = TOKEN_UNKNOWN;
	size_t start = self->cursor.current;

	source_cursor_advance(&self->cursor);

	float x = 0.5F;
	
	if(
		source_cursor_is(&self->cursor, 'x') || source_cursor_is(&self->cursor, 'X') ||
		source_cursor_is(&self->cursor, 'o') || source_cursor_is(&self->cursor, 'O') ||
		source_cursor_is(&self->cursor, 'b') || source_cursor_is(&self->cursor, 'B')
	) {
		source_cursor_advance(&self->cursor);
	} else {
		// Normal digit
		while(isdigit(source_cursor_current(&self->cursor))) {
			source_cursor_advance(&self->cursor);
		}
	}

	if(
		source_cursor_is(&self->cursor, 'u') || source_cursor_is(&self->cursor, 'U') ||
		source_cursor_is(&self->cursor, 'i') || source_cursor_is(&self->cursor, 'I') ||
		source_cursor_is(&self->cursor, 'f') || source_cursor_is(&self->cursor, 'F')
	) {
		// Type override
		source_cursor_advance(&self->cursor);
	}

	return make_token(self, kind, start);
}

// keywords :: All language keywords combined into a single string
static const char keywords[] = 
{

#define TOKEN(x, y) #x "\0"
#include "token_kinds.def"
#undef TOKEN

};

// keyword_exists :: If string exists within keywords, returns the index; returns -1 if keywords
// doesnt contain string
INLINE int keyword_exists(const char* start, size_t length)
{
	size_t index = 0;

	for(size_t i = 0; keywords[index] != '\0'; i++) {
		if(length == strlen(&keywords[index]) && strncmp(start, &keywords[index], length) == 0) {
			return i;
		}

		while(keywords[index] != '\0') {
			index++;
		}
		index++;
	}

	return -1;
}