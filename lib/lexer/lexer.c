// Copyright (c) 2026 Justin Wallace
// lexer.c - Lexical analysis

#include "lexer.h"
#include "token.h"
#include "common.h"
#include <ctype.h>

static const char keywords[];
static int keyword_exists(const char* start, size_t length);
INLINE Token next_token(Lexer* lexer);
INLINE Token next_symbol_or_operator(Lexer* lexer);
INLINE Token next_keyword_or_identifier(Lexer* lexer);

// next_keyword :: Tokenizes all characters in SourceFile
extern void lexer_tokenize(Lexer* lexer, SourceFile* source_file, TokenStream* token_stream)
{
	lexer->source_file = source_file;
	lexer->tokens = token_stream;

	source_cursor_init(&lexer->cursor, lexer->source_file);
	
	for(;;) {
		Token t = next_token(lexer);

		token_stream_push_back(lexer->tokens, &t);

		if(t.kind == TOKEN_EOF) {
			break;
		}
	}

	for(size_t i = 0; i < lexer->tokens->length; i++) {
		Token* t = token_stream_at(lexer->tokens, i);
		printf("token %02d: %.*s \n", t->kind, (int)t->source.length, t->source.ptr);
	}

	// array_for_each(Token*, t, lexer->tokens) {
	// 	// printf("token: %.*s %d\n", t->source.length, t->source.ptr, t->kind);
	// }
}


// skip_whitespace :: Advances cursor until non-whitespace character is reached
INLINE void skip_whitespace(Lexer* lexer)
{
	while(isspace(source_cursor_current(&lexer->cursor)) || source_cursor_is(&lexer->cursor, '\t')) {
		source_cursor_advance(&lexer->cursor);
	}
}

INLINE Token make_token(Lexer* lexer, TokenKind kind, size_t start)
{
	Token tok = {0};
	tok.kind = kind;
	tok.source.ptr = source_cursor_string_at(&lexer->cursor, start);
	tok.source.length = lexer->cursor.current - start;

	return tok;
}

// next_keyword :: Returns the next token
INLINE Token next_token(Lexer* lexer)
{
	skip_whitespace(lexer);

	Token tok = {0};

	// Keyword or identifier
	if(isalpha(source_cursor_current(&lexer->cursor))) {
		tok = next_keyword_or_identifier(lexer);
		goto end;
	}

	// String literal
	if(source_cursor_is(&lexer->cursor, '\"')) {
		tok = next_symbol_or_operator(lexer);
		goto end;
	}

	// Numeric literal
	if(isdigit(source_cursor_current(&lexer->cursor))) {
		tok = next_symbol_or_operator(lexer);
		goto end;
	}

	// EOF token
	if(source_cursor_is(&lexer->cursor, '\0')) {
		tok = next_symbol_or_operator(lexer);
		goto end;
	}

	// Fall back to symbol or operator, or error token
	tok = next_symbol_or_operator(lexer);

end:

	return tok;
}

INLINE Token next_symbol_or_operator(Lexer* lexer)
{
	TokenKind kind = TOKEN_IDENTIFIER;
	size_t start = lexer->cursor.current;

	source_cursor_advance(&lexer->cursor);

	if(source_cursor_is(&lexer->cursor, '\0')) {
		kind = TOKEN_EOF;
	}

	return make_token(lexer, kind, start);
}
// next_keyword :: Returns the next keyword
INLINE Token next_keyword_or_identifier(Lexer* lexer)
{
	TokenKind kind = TOKEN_IDENTIFIER;
	size_t start = lexer->cursor.current;

	while(isalnum(source_cursor_current(&lexer->cursor)) || source_cursor_is(&lexer->cursor, '_')) {
		source_cursor_advance(&lexer->cursor);
	}

	int kw = keyword_exists((const char*)source_cursor_string_at(&lexer->cursor, start), lexer->cursor.current - start);

	if(kw != -1) {
		kind = kw;
	}

	return make_token(lexer, kind, start);
}

static const char keywords[] = 
{

#define TOKEN(x, y) #x "\0"
#include "token_kinds.def"
#undef TOKEN

};

// keyword_exists :: Returns index of string in keywords, returns -1 if keywords doesnt caint string
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