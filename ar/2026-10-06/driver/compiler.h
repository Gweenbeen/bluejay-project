// compiler.h

#pragma once

#include "array.h"

// CompilerContext :: Compiler state
struct CompilerContext
{
	int argc;
	const char** argv;
};

extern int compiler_run(int argc, const char* argv[]);
extern void compiler_main(struct CompilerContext* compiler_context, int argc, const char* argv[]);
extern void compiler_cleanup(struct CompilerContext* compiler_context);