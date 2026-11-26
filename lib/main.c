// main.c - Canonical program entry point

#define NOASSERT

#include "driver/compiler.h"

int main(int argc, const char *argv[])
{
	compiler_run(argc, argv);

	return 0;
}