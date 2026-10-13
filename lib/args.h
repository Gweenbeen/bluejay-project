// args.h - Command line argument parsing API

#pragma once


enum ArgOptionKind
{
	ARG_OPTION_BOOL,
	ARG_OPTION_STRING,
	ARG_OPTION_INT,
	ARG_OPTION_FLOAT,
	ARG_OPTION_FLAG,
	ARG_OPTION_UNKNOWN,
	ARG_OPTION_END,
};

struct ArgOption
{
	enum ArgOptionKind kind;

	const char *short_name;
	const char *name;
	int flags;
	const uint8_t *value;
	const uint8_t *alt_value;

	const char *help;
};

struct Args
{
	DEFINE_ARRAY_HEADER(struct ArgOption);
};

DEFINE_ARRAY_IMPL(struct ArgOption, arg_option, struct ArgOption);