// Copyright (c) 2026 Justin Wallace
// lexer.h - Lexical pass

#pragma once

#include "token.h"
#include "source/source_cursor.h"

// Lexer :: Manages lexical state
typedef struct Lexer
{
	SourceFile* source_file;
	SourceCursor cursor;

	TokenStream* tokens;
} Lexer;

extern void lexer_tokenize(Lexer* lexer, SourceFile* source_file, TokenStream* token_stream);