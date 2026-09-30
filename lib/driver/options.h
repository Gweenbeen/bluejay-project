// Copyright (c) 2026 Justin Wallace
// options.h

#pragma once

#include "array.h"

// Option :: Compilation option
typedef struct Option
{
	StringView string;
	uint8_t* value;
} Option;

// BuildOptions :: Array of options
typedef struct OptionList
{
	DEFINE_ARRAY_STRUCT_IMPL(Option);

	struct
	{
		size_t index;
	} Cursor;
} OptionList;

DEFINE_ARRAY_API_IMPL(Option, OptionList, option_list);

INLINE void option_list_from_argv(OptionList* option_list, int argc, const char* argv[])
{
	for(size_t i = 0; i < argc; i++) {
		option_list_push_back(option_list, &(Option){ .string = string_view_from_cstring(argv[i], strlen(argv[i])), .value = NULL } );
	}
}

INLINE void parse_arguments(CompilerContext* compiler_context)
{
	// First argument is the name of the application, so we start at one
	for(size_t i = 1; i < compiler_context->argc; i++) {
		switch(compiler_context->argv[i][0]) {
		case '-':
			switch(compiler_context->argv[i][1]) {
			case '-':
				break;
			case 'c':
				for(size_t j = i + 1; j < compiler_context->argc; j++) {
					printf("%s\n", compiler_context->argv[j]);
					i++;
				}

				break;
			}
			break;
		default:
			printf("Did not recognize command \"%s\"\n", compiler_context->argv[i]);
		}
	}
}