// compiler.c

#include "compiler.h"
#include "source/source_file.h"
#include "lexer/lexer.h"
#include "common.h"

extern int compiler_run(int argc, const char* argv[])
{
	CompilerContext compiler = {0};
	
	compiler_main(&compiler, argc, argv);
	compiler_cleanup(&compiler);

	return 0;
}

// compiler_main :: Canonical entry point for compiler
extern void compiler_main(CompilerContext* compiler_context, int argc, const char* argv[])
{
	compiler_context->argc = argc;
	compiler_context->argv = argv;

	// parse_options(&compiler_context);

	// Tokenize and parse
	for(size_t i = 1; i < argc; i++) {
		SourceFile source_file = {0};
		Lexer lexer = {0};
		
		TokenStream tokens = {0};
		token_stream_init(&tokens);

		source_file_read(&source_file, argv[i]);
		lexer_tokenize(&lexer, &source_file, &tokens);

		source_file_free(&source_file);
		token_stream_free(&tokens);
	}
}

// compiler_cleanup :: Release of all compiler resources
extern void compiler_cleanup(CompilerContext* compiler_context)
{
	//
}