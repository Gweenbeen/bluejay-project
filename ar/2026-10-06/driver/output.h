// out.h

#pragma once

#include "config.h"

typedef struct Output
{
	Config config;

	const char* name;
	const char* string;
} Output;

STATIC void write_to_output(Output* self)
{
	FILE* f = fopen(self->name, "w");

	self->string = 
	"this is a demo!!!";

	fwrite(self->string, 1, strlen(self->string), f);

	fclose(f);
}