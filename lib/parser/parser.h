// Copyright (c) 2026 Justin Wallace
// parser.h - Parsing context

#pragma once

typedef struct ASTContext ASTContext;
typedef struct TokenStream TokenStream;

typedef struct Parser
{
	ASTContext* ast;
	Scope* scope;
	TokenStream* tokens;
} Parser;

INLINE void 