// lexer.h - Lexical analysis

#pragma once

#include "source/source_cursor.h"

struct Token;
struct TokenSream;
struct SourceFile;

// Lexer :: Tokenizes source
struct Lexer
{
	struct SourceCursor cursor;
	struct TokenStream *tokens;
};

// lexer_run :: Tokenizes an input SourceFile, and populates TokenStream with Token
extern void lexer_run(struct SourceFile *source, struct TokenStream *tokens);