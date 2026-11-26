// token.h - Lexical token

#pragma once

#include "array.h"
#include "common.h"

// TokenKind :: All token types
enum TokenKind
{	

#define DEFINE_TOKEN(name, t) t, 
#include "token/token_kinds.h"
#undef DEFINE_TOKEN

	TOKEN_UNKNOWN,
	TOKEN_IDENTIFIER,
	TOKEN_STRING_LITERAL,
	TOKEN_NUMERIC_LITERAL,
	TOKEN_COMMENT,
	TOKEN_EOF = -1, 
};

// Token :: Lexical token to be used for parsing
struct Token
{
	enum TokenKind kind;
	struct StringView source;
};

// Token :: Array of Token to be used for Parsing
struct TokenStream
{
	DEFINE_ARRAY_HEADER(struct Token);

	size_t current;
};
DEFINE_ARRAY_IMPL(struct TokenStream, token_stream, struct Token);


static enum TokenKind token_stream_current(struct TokenStream *self)
{
	return self->ptr[self->current].kind;
}

static enum TokenKind token_stream_peek(struct TokenStream *self)
{
	return self->ptr[self->current + 1].kind;
}

static enum TokenKind token_stream_prev(struct TokenStream *self)
{
	return self->ptr[self->current - 1].kind;
}

static void token_stream_advance(struct TokenStream *self)
{
	++self->current;
}

static void token_stream_rewind(struct TokenStream *self)
{
	--self->current;
}

static bool token_stream_is(struct TokenStream *self, enum TokenKind kind)
{
	if (self->ptr[self->current].kind) {
		return true;
	}
	return false;
}

static bool token_stream_expect(struct TokenStream *self, enum TokenKind kind)
{
	return true;
}

[[maybe_unused]] static void token_print(struct Token *tok)
{
	if (tok == nullptr) {
		printf("No token!\n");
		return;
	}

	if (tok->kind == TOKEN_EOF) {
		printf("token -1 = EOF\n");
		return;
	}

	printf("token %03d = %.*s\n", 
		tok->kind,
		(int)tok->source.length, 
		tok->source.ptr
	);
}

[[maybe_unused]] static void token_stream_print_tokens(struct TokenStream *tokens)
{
	ARRAY_FOR_EACH_PTR (struct Token *, i, tokens) {
		token_print(i);
	}
}