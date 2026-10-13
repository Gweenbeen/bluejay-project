// Copyright (c) 2026 Justin Wallace
// lexer.h - Lexical pass

#pragma once

#include "token.h"
#include "source/source_cursor.h"

// Lexer :: Manages lexical state
typedef struct Lexer
{
	struct SourceFile* source_file;
	SourceCursor cursor;

	TokenStream* tokens;
} Lexer;

extern void lexer_tokenize(Lexer* self, struct SourceFile* source_file, TokenStream* token_stream);