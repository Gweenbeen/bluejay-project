// lexer.h - Lexical analyzer

#pragma once

#include "token.h"

// Lexer :: Lexical analysis
struct Lexer
{
	struct TokenStream tokens;

	size_t current;
};

extern void lexer_tokenize(struct Lexer *self);