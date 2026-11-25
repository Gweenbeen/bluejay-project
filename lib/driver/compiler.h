// compiler.h - Compilation context
#pragma once

#include "array.h"
#include "stringt.h"
#include "source/source_file.h"
#include "token/token.h"
#include "lexer/lexer.h"
#include "ast/ast.h"
#include "parser/parser.h"
#include "driver/options.h"
#include <stdio.h>

struct CompilerContext
{
	struct Options options;
	struct ModuleArray modules;
};

void compiler_run(int argc, const char *argv[])
{
	struct CompilerContext self = {};
	module_array_init(&self.modules);

	options_parse(&self.options, &self.modules, argc, argv);

	ARRAY_FOR_EACH (struct Module *, i, self.modules) {
		printf("\tcompiling a unit...\n");

		source_file_load(&i->source, i->input_path);

		token_stream_init(&i->tokens);

		lexer_run(&i->source, &i->tokens); 

		ast_context_init(&i->ast);

		parser_run(&i->ast, nullptr, &i->tokens);

		ast_node_print_tree(i->ast.root, 0);

		printf("\tdone!\n");
	}

	struct String write = {0};
	string_init(&write);

	string_append(&write, "Outputting to ");
	string_append(&write, self.options.output_path);
	string_append(&write, "\n\n");
	
	ARRAY_FOR_EACH (struct Module *, i, self.modules) {
		string_append(&write, "Outputting file...\n\n");

		string_append_with_length(&write, i->source.ptr, i->source.length);
	}

	FILE *out = fopen(self.options.output_path, "w+");
	fprintf(out, "%.*s\n", (int)write.length, write.ptr);
	fclose(out);

	string_free(&write);

	ARRAY_FOR_EACH (struct Module *, i, self.modules) {
		printf("\tcleanup\n");

		ast_context_free(&i->ast);
		token_stream_free(&i->tokens);
		source_file_free(&i->source);
	}

	module_array_free(&self.modules);
}