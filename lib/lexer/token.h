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
	StringView source;
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

INLINE Token* token_stream_current(TokenStream* token_stream) { return token_stream_at(token_stream, token_stream->Cursor.current); }
INLINE Token* token_stream_peek(TokenStream* token_stream) { return token_stream_at(token_stream, token_stream->Cursor.current + 1); }
INLINE void token_stream_advance(TokenStream* token_stream) { token_stream->Cursor.current++; };
INLINE bool token_stream_is_out_of_bounds(TokenStream* token_stream) { return token_stream->Cursor.current >= token_stream->length; };
INLINE bool token_stream_expect(TokenStream* token_stream, Token* expect) { return token_stream_at(token_stream, token_stream->Cursor.current) == expect; };
INLINE bool token_stream_is(TokenStream* token_stream, TokenKind kind) { return token_stream_at(token_stream, token_stream->Cursor.current)->kind == kind; };