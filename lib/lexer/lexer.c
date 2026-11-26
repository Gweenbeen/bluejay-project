// lexer.c - From "lexer.h"

#include "lexer/lexer.h"
#include "token/token.h"
#include "source/source_file.h"
#include "source/source_cursor.h"
#include "array.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

// source_view_make :: Creates a struct SourceView
static struct SourceView source_view_make(struct SourceCursor *cursor, size_t start);

// token_make :: Creates a struct Token
static struct Token token_make(struct Lexer *self, size_t start, enum TokenKind kind);

// keywords :: Character representation of all language keywords
static constexpr const char keywords[];

// keyword_exists :: If keyword exists, return position of word in 'keywords[]', -1 if false
static int keyword_exists(const char *start, size_t length);

// skip_whitespace :: Skips all whitespace characters
static void skip_whitespace(struct Lexer *self);

// next_token :: Dispatches the next Token
static struct Token next_token(struct Lexer *self);

// next_keyword_or_identifier :: Returns the next keyword Token or identifier Token
static struct Token next_keyword_or_identifier(struct Lexer *self);

// next_string_literal :: Returns the next string literal Token
static struct Token next_string_literal(struct Lexer *self);

// next_numeric_literal :: Returns the next numeric literal Token
static struct Token next_numeric_literal(struct Lexer *self);

// next_symbol_or_operator :: Returns the next symbol Token or Operator Token
static struct Token next_symbol_or_operator(struct Lexer *self);


extern void lexer_run(struct SourceFile *source, struct TokenStream *tokens)
{
	ASSERT(source != nullptr);
	ASSERT(tokens != nullptr);

	struct Lexer self = {
		.cursor = source_cursor_make(source),
		.tokens = tokens,
	};

	for (struct Token tok = {0}; tok.kind != TOKEN_EOF;)
	{
		tok = next_token(&self);
		token_stream_push_back(self.tokens, tok);
	}
}

static constexpr const char keywords[] = {

#define DEFINE_TOKEN(x, y) #x "\0"
#include "token/token_kinds.h"
#undef DEFINE_TOKEN

};

static int keyword_exists(const char *start, size_t length)
{
	size_t index = 0;
	for (size_t i = 0; keywords[index] != '\0'; i++) {
		if (length == strlen(&(keywords)[index]) && strncmp(&(keywords)[index], start, length) == 0) {
			return i;
		}

		while (keywords[index] != '\0') {
			index++;
		}
		index++;
	}

	return -1;
}

static struct Token token_make(struct Lexer *self, size_t start, enum TokenKind kind)
{
	return (struct Token){
		.kind = kind,
		.source = string_view_make((const uint8_t *)&(self->cursor.source->ptr[start]), self->cursor.current - start),
	};
}

// extern void lexer_run(struct Lexer *self, struct TokenStream *tokens, struct SourceFile *file)
// {
	// printf("doing things...\n"); 
// 
	// self->tokens = tokens;
// 
	// source_cursor_init(&self->cursor, file);
// 
	// struct Token tok = {0};
	// while (tok.kind != TOKEN_EOF) {
		// tok = next_token(self);
		// token_stream_push_back(self->tokens, tok);
	// }
// }

static void skip_whitespace(struct Lexer *self)
{
	while (isspace(source_cursor_current(&self->cursor)) || source_cursor_is(&self->cursor, '\t')) {
		source_cursor_advance(&self->cursor);
	}
}

static struct Token next_token(struct Lexer *self)
{
	skip_whitespace(self);

	struct Token tok = {0};

	if (source_cursor_is(&self->cursor, '\0')) {
		tok.kind = TOKEN_EOF;
		return tok;
	}

	if (isalpha(source_cursor_current(&self->cursor))) {
		return next_keyword_or_identifier(self);
	}
	
	if (source_cursor_is(&self->cursor, '\"')) {
		return next_string_literal(self);
	}

	if (isdigit(source_cursor_current(&self->cursor))) {
		return next_numeric_literal(self);
	}	

	return next_symbol_or_operator(self);
}

static struct Token next_keyword_or_identifier(struct Lexer *self)
{
	size_t start = self->cursor.current;
	enum TokenKind kind = TOKEN_IDENTIFIER;

	while (isalnum(source_cursor_current(&self->cursor)) || source_cursor_is(&self->cursor, '_')) {
		source_cursor_advance(&self->cursor);
	}

	int kw = keyword_exists(&(self->cursor.source->ptr[start]), self->cursor.current - start);
	if (kw != -1) {
		kind = kw;
	}

	return token_make(self, start, kind);
}

static struct Token next_string_literal(struct Lexer *self)
{
	source_cursor_advance(&self->cursor);

	size_t start = self->cursor.current;
	while (!source_cursor_is(&self->cursor, '\"')) {
		source_cursor_advance(&self->cursor);
	}

	struct Token tok = token_make(self, start, TOKEN_STRING_LITERAL);

	source_cursor_advance(&self->cursor);

	return tok;
}

static struct Token next_numeric_literal(struct Lexer *self)
{
	size_t start = self->cursor.current;
	enum TokenKind kind = TOKEN_NUMERIC_LITERAL;

	if (source_cursor_is(&self->cursor, 'x') || source_cursor_is(&self->cursor, 'X')) {
		while (
			isdigit(source_cursor_current(&self->cursor)) || 
			source_cursor_is(&self->cursor, 'a') ||
			source_cursor_is(&self->cursor, 'A') ||
			source_cursor_is(&self->cursor, 'b') ||
			source_cursor_is(&self->cursor, 'B') ||
			source_cursor_is(&self->cursor, 'c') ||
			source_cursor_is(&self->cursor, 'C') ||
			source_cursor_is(&self->cursor, 'd') ||
			source_cursor_is(&self->cursor, 'D') ||
			source_cursor_is(&self->cursor, 'e') ||
			source_cursor_is(&self->cursor, 'E') ||
			source_cursor_is(&self->cursor, 'f') ||
			source_cursor_is(&self->cursor, 'F')) 
		{
			source_cursor_advance(&self->cursor);
		}
	} else if (source_cursor_is(&self->cursor, 'b') || source_cursor_is(&self->cursor, 'B')) {
		while (
			source_cursor_is(&self->cursor, '0') ||
			source_cursor_is(&self->cursor, '1')) 
		{
			source_cursor_advance(&self->cursor);
		}
	} else if (source_cursor_is(&self->cursor, 'o') || source_cursor_is(&self->cursor, 'O')) {
		while (
			isdigit(source_cursor_current(&self->cursor)) || 
			source_cursor_is(&self->cursor, '0') ||
			source_cursor_is(&self->cursor, '1') ||
			source_cursor_is(&self->cursor, '2') ||
			source_cursor_is(&self->cursor, '3') ||
			source_cursor_is(&self->cursor, '4') ||
			source_cursor_is(&self->cursor, '5') ||
			source_cursor_is(&self->cursor, '6') ||
			source_cursor_is(&self->cursor, '7'))
		{
			source_cursor_advance(&self->cursor);
		}
	} else {
		while (isalnum(source_cursor_current(&self->cursor)) || source_cursor_is(&self->cursor, '\'')) {
			source_cursor_advance(&self->cursor);
		}
	}

	return token_make(self, start, kind);
}

static bool is_multi_char_operator(const char *start, size_t length, const char *expected)
{
	return (strncmp(start, expected, length) == 0);
}

static enum TokenKind symbol_kind(struct Lexer *self, size_t start)
{
	const char *ptr = &(self->cursor.source->ptr[start]);

	source_cursor_advance(&self->cursor);
	source_cursor_advance(&self->cursor);

	if (is_multi_char_operator(ptr, 3, "/%=") || is_multi_char_operator(ptr, 3, "=/%")) {
		return TOKEN_ASSIGN_IDIV;
	}
	if (is_multi_char_operator(ptr, 3, "<<=") || is_multi_char_operator(ptr, 3, "=<<")) {
		return TOKEN_ASSIGN_LEFT_SHIFT;
	}
	if (is_multi_char_operator(ptr, 3, ">>=") || is_multi_char_operator(ptr, 3, "=>>")) {
		return TOKEN_ASSIGN_RIGHT_SHIFT;
	}
	if (is_multi_char_operator(ptr, 3, "<<<")) {
		return TOKEN_ASSIGN_ROTATE_LEFT;
	}
	if (is_multi_char_operator(ptr, 3, ">>>")) {
		return TOKEN_ASSIGN_ROTATE_RIGHT;
	}
	if (is_multi_char_operator(ptr, 3, "...")) {
		return TOKEN_ELLIPSIS;
	}

	source_cursor_rewind(&self->cursor);

	if (is_multi_char_operator(ptr, 2, ":=")) {
		return TOKEN_INITIALIZE;
	}
	if (is_multi_char_operator(ptr, 2, "+=") || is_multi_char_operator(ptr, 2, "=+")) {
		return TOKEN_ASSIGN_ADD;
	}
	if (is_multi_char_operator(ptr, 2, "-=") || is_multi_char_operator(ptr, 2, "=-")) {
		return TOKEN_ASSIGN_SUB;
	}
	if (is_multi_char_operator(ptr, 2, "*=") || is_multi_char_operator(ptr, 2, "=*")) {
		return TOKEN_ASSIGN_MULT;
	}
	if (is_multi_char_operator(ptr, 2, "/=") || is_multi_char_operator(ptr, 2, "=/")) {
		return TOKEN_ASSIGN_DIV;
	}
	if (is_multi_char_operator(ptr, 2, "%=") || is_multi_char_operator(ptr, 2, "=%")) {
		return TOKEN_ASSIGN_MOD;
	}
	if (is_multi_char_operator(ptr, 2, "&=") || is_multi_char_operator(ptr, 2, "=&")) {
		return TOKEN_ASSIGN_AND;
	}
	if (is_multi_char_operator(ptr, 2, "|=") || is_multi_char_operator(ptr, 2, "=|")) {
		return TOKEN_ASSIGN_OR;
	}
	if (is_multi_char_operator(ptr, 2, "~=") || is_multi_char_operator(ptr, 2, "=~")) {
		return TOKEN_ASSIGN_NOT;
	}
	if (is_multi_char_operator(ptr, 2, "^=") || is_multi_char_operator(ptr, 2, "=^")) {
		return TOKEN_ASSIGN_XOR;
	}
	if (is_multi_char_operator(ptr, 2, "/%")) {
		return TOKEN_IDIV;
	}
	if (is_multi_char_operator(ptr, 2, "++")) {
		return TOKEN_INCREMENT;
	}
	if (is_multi_char_operator(ptr, 2, "--")) {
		return TOKEN_DECREMENT;
	}
	if (is_multi_char_operator(ptr, 2, "&&")) {
		return TOKEN_AND;
	}
	if (is_multi_char_operator(ptr, 2, "||")) {
		return TOKEN_OR;
	}
	if (is_multi_char_operator(ptr, 2, "==")) {
		return TOKEN_EQ;
	}
	if (is_multi_char_operator(ptr, 2, "!=")) {
		return TOKEN_NEQ;
	}
	if (is_multi_char_operator(ptr, 2, ">=")) {
		return TOKEN_GTOEQ;
	}
	if (is_multi_char_operator(ptr, 2, "=<")) {
		return TOKEN_LTOEQ;
	}
	if (is_multi_char_operator(ptr, 2, "->")) {
		return TOKEN_ARROW;
	}
	if (is_multi_char_operator(ptr, 2, "::")) {
		return TOKEN_SCOPE_RESOLUTION;
	}

	source_cursor_rewind(&self->cursor);

	if (source_cursor_is(&self->cursor, '=')) {
		return TOKEN_ASSIGN;
	}
	if (source_cursor_is(&self->cursor, '+')) {
		return TOKEN_PLUS;
	}
	if (source_cursor_is(&self->cursor, '-')) {
		return TOKEN_HYPHEN;
	}
	if (source_cursor_is(&self->cursor, '*')) {
		return TOKEN_ASTERISK;
	}
	if (source_cursor_is(&self->cursor, '/')) {
		return TOKEN_SLASH;
	}
	if (source_cursor_is(&self->cursor, '%')) {
		return TOKEN_PERCENT;
	}
	if (source_cursor_is(&self->cursor, '&')) {
		return TOKEN_BIT_AND;
	}
	if (source_cursor_is(&self->cursor, '|')) {
		return TOKEN_BIT_OR;
	}
	if (source_cursor_is(&self->cursor, '~')) {
		return TOKEN_BIT_NOT;
	}
	if (source_cursor_is(&self->cursor, '^')) {
		return TOKEN_BIT_XOR;
	}
	if (source_cursor_is(&self->cursor, '>')) {
		return TOKEN_GT;
	}
	if (source_cursor_is(&self->cursor, '<')) {
		return TOKEN_LT;
	}
	if (source_cursor_is(&self->cursor, '?')) {
		return TOKEN_TERNARY;
	}
	if (source_cursor_is(&self->cursor, '(')) {
		return TOKEN_LPAREN;
	}
	if (source_cursor_is(&self->cursor, ')')) {
		return TOKEN_RPAREN;
	}
	if (source_cursor_is(&self->cursor, '{')) {
		return TOKEN_LCURLY;
	}
	if (source_cursor_is(&self->cursor, '}')) {
		return TOKEN_RCURLY;
	}
	if (source_cursor_is(&self->cursor, '[')) {
		return TOKEN_LBRACE;
	}
	if (source_cursor_is(&self->cursor, ']')) {
		return TOKEN_RBRACE;
	}
	if (source_cursor_is(&self->cursor, ':')) {
		return TOKEN_COLON;
	}
	if (source_cursor_is(&self->cursor, ';')) {
		return TOKEN_SEMICOLON;
	}
	if (source_cursor_is(&self->cursor, ',')) {
		return TOKEN_COMMA;
	}
	if (source_cursor_is(&self->cursor, '.')) {
		return TOKEN_PERIOD;
	}
	if (source_cursor_is(&self->cursor, '\"')) {
		return TOKEN_QUOTE;
	}
	if (source_cursor_is(&self->cursor, '\'')) {
		return TOKEN_APOSTROPHE;
	}
	if (source_cursor_is(&self->cursor, '_')) {
		return TOKEN_UNDERSCORE;
	}
	if (source_cursor_is(&self->cursor, '$')) {
		return TOKEN_DOLLAR;
	}
	if (source_cursor_is(&self->cursor, '@')) {
		return TOKEN_AT;
	}
	if (source_cursor_is(&self->cursor, '\\')) {
		return TOKEN_BACKSLASH;
	}

	return TOKEN_UNKNOWN;
}

static struct Token next_symbol_or_operator(struct Lexer *self)
{
	size_t start = self->cursor.current;
	enum TokenKind kind = symbol_kind(self, start);

	source_cursor_advance(&self->cursor);

	return token_make(self, start, kind);
}