// main.c - Canonical program entry point

#include "source/source_file.h"
#include "lexer/token.h"

#include "array_impl.h"

int main(int argc, const char *argv[])
{
	ASSERT(1 == 2);
	test();
}
// struct IntArray
// {
	// DEFINE_ARRAY_HEADER(int);
// };
// DEFINE_ARRAY_IMPL(struct IntArray, int_array, int);
// 
// int main(int argc, const char *argv[])
// {
// 
	// struct IntArray arr = {0};
// 
	// int_array_init(&arr);
// 
	// int_array_push_back(&arr, 50);
	// 
	// for (size_t i = 0; i < 14; i++) {
		// int_array_push_back(&arr, i + 10);
	// }
// 
	// ARRAY_FOR_EACH_CONST (int *, i, arr) {
		// printf("nubmah = %d\n", *i);
	// }
// 
	// int_array_free(&arr);
// 
	// printf("Hello, world!\n");
// 
	// return 0;
// }