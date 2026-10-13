// module.h

#pragma once

#include "source/source_file.h"
#include "lexer/lexer.h"

typedef struct Ast Ast;
typedef struct Scope Scope;

// Module :: A single compilation unit
typedef struct Module
{
	SourceFile source_file;
	TokenStream token_stream;

	Ast* ast_decl;
	Scope* scope_decl;
} Module;

// Modules :: 
typedef struct Modules // Array<Module>
{
	DEFINE_ARRAY_STRUCT_IMPL(Module);
} Modules;