// compiler.h

#pragma once

#include "array.h"

// CompilerContext :: Compiler state
typedef struct CompilerContext
{
	int argc;
	const char** argv;
} CompilerContext;

extern int compiler_run(int argc, const char* argv[]);
extern void compiler_main(CompilerContext* compiler_context, int argc, const char* argv[]);
extern void compiler_cleanup(CompilerContext* compiler_context);