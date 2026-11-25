// options.h - Compilation options

#pragma once

#include "module.h"
#include <stddef.h>

constexpr static size_t MAX_INPUT = 512;

struct Options
{
	bool mode_compile;

	bool verbosity_verbose;
	bool verbosity_silent;
	bool no_note;
	bool no_warning;
	bool no_exception;

	size_t min_memory;
	size_t max_memory;

	bool enable_threads;
	size_t max_threads;
	size_t min_threads;


	bool enable_bench;
	const char *bench_path;

	bool enable_diagnostic;
	const char *diagnostic_path;

	const char *output_path;
};

const char *default_search_paths[] = {
	".",
};

static void options_parse(struct Options* self, struct ModuleArray* modules, int argc, const char *argv[])
{
	self->output_path = ".";
	bool compile = false;

	for (size_t i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && i < argc)
		{
			if (argv[i][1] == 'c' && i < argc) {
				++i;

				while (argv[i][0] != '-' && i < argc) {
					if (modules->length > MAX_INPUT) {
						break;
					}

					const char *path = argv[i];

					struct Module module = {
						.input_path = path,
					};

					module_array_push_back(modules, module);

					++i;
				}
			} 

			if (argv[i][1] == 'o' && i < argc) {
				++i;
				self->output_path = argv[i];
			}
		}
		else
		{
			printf("Unexpected entry (%s)\n", argv[i]);
		}
	}
}