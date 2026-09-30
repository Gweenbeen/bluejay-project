// Copyright (c) 2026 Justin Wallace
// main.c - Main

#include "driver/compiler.h"

#include "string_table.h"
/*

local state
	source text
	tokens 
	ast
	scope
	symbol table
local pass
	load source file
	tokenization
	parsing
	semantic analysis
global state
	build options
	type context

*/
int main(int argc, const char* argv[])
{
	printf("%zu\n\n", sizeof(StringTableEntry));

	return compiler_run(argc, argv);
}