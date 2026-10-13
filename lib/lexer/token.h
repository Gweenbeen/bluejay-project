// token.h

#pragma once

#include "common.h"
#include "array.h"
#include "source/source_view.h"

// TokenKind :: What kind of Token
enum TokenKind
{
	TOKEN_EOF
};

// Token :: Lexical token for parsing
struct Token
{
	enum TokenKind kind;
	struct SourceView source;
};

// TokenStream :: Array of Token
struct TokenStream
{
	DEFINE_ARRAY_HEADER(struct Token);
};

DEFINE_ARRAY_IMPL(struct TokenStream, token_stream, struct Token);