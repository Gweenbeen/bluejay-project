// module.h

#pragma once

// Module :: A single compilation unit
struct Module
{
	const char *input_path;

	struct SourceFile source;
	struct TokenStream tokens;
	struct ASTContext ast;
	struct ScopeContext *scope;

	// struct Config config;
};

// ModuleArray :: Array of Module
struct ModuleArray
{
	DEFINE_ARRAY_HEADER(struct Module);
};
DEFINE_ARRAY_IMPL(struct ModuleArray, module_array, struct Module);