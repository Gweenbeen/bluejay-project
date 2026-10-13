// token.h

#pragma once

#include "common.h"
#include "array.h"

typedef enum TokenKind
{	

#define TOKEN(x, y) y,
#include "token_kinds.def"
#undef TOKEN

} TokenKind;

// Token :: Lexical token
typedef struct Token
{
	TokenKind kind;
	struct StringView source;
} Token;

// TokenStream :: Array of tokens to be parsed
typedef struct TokenStream
{
	DEFINE_ARRAY_STRUCT_IMPL(Token);

	struct
	{
		size_t current;
		size_t last;
	} Cursor;
} TokenStream;

DEFINE_ARRAY_API_IMPL(Token, TokenStream, token_stream);

INLINE Token* token_stream_current(TokenStream* self) { return token_stream_at(self, self->Cursor.current); }
INLINE Token* token_stream_peek(TokenStream* self) { return token_stream_at(self, self->Cursor.current + 1); }
INLINE void token_stream_advance(TokenStream* self) { self->Cursor.current++; };
INLINE bool token_stream_is_out_of_bounds(TokenStream* self) { return self->Cursor.current >= self->length; };
INLINE bool token_stream_expect(TokenStream* self, Token* expect) { return token_stream_at(self, self->Cursor.current) == expect; };
INLINE bool token_stream_is(TokenStream* self, TokenKind kind) { return token_stream_at(self, self->Cursor.current)->kind == kind; };