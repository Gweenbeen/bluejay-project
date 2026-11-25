// stringt.h - String API

#pragma once

#include <string.h>

struct String
{
	DEFINE_ARRAY_HEADER(char);
};
DEFINE_ARRAY_IMPL(struct String, string, char);

// should this use variadic args?
static void string_append(struct String *self, const char *string)
{
	string_reserve(self, strlen(string) + 1);

	for (size_t i = 0; i < strlen(string); ++i) {
		string_push_back(self, string[i]);
	}

	self->ptr[self->length] = '\0';
}

static void string_append_with_length(struct String *self, const char *string, size_t length)
{
	string_reserve(self, length + 1);

	for (size_t i = 0; i < length; ++i) {
		string_push_back(self, string[i]);
	}

	self->ptr[self->length] = '\0';
}

static void string_concat(struct String *self, const char *to, const char *from)
{
	string_reserve(self, strlen(to) + strlen(from) + 1);

	for (size_t i = 0; i < strlen(to); ++i) {
		string_push_back(self, to[i]);
	}

	for (size_t i = 0; i < strlen(from); ++i) {
		string_push_back(self, from[i]);
	}

	self->ptr[self->length] = '\0';
}

// void test(void) {
	
	// struct String string = {0};
	// string_init(&string);

	// string_append(&string, "JADIUSDJJJJJLAKDJSLADJIOPADJPASDJIOWEJDUIJWEPODJWEIDJLLKASJDKLWEUPJIODJJSKLDADOPIJASKDpajksdioaj");

	// string_concat(&string, "Hello, ", "world!");

	// string_append(&string, "JADIUSDJJJJJLAKDJSLADJIOPADJPASDJIOWEJDUIJWEPODJWEIDJLLKASJDKLWEUPJIODJJSKLDADOPIJASKDpajksdioaj");
	// string_append(&string, "JADIUSDJJJJJLAKDJSLADJIOPADJPASDJIOWEJDUIJWEPODJWEIDJLLKASJDKLWEUPJIODJJSKLDADOPIJASKDpajksdioajYYAYHAEHA");
	// string_concat(&string, "STIRTING, ", "ADKSLADJASKA!");

	// for (size_t i = 0; i < 999; ++i) {
		// string_append(&string, "JADIUSDJJJJJLAKDJSLADJIOPADJPASDJIOWEJDUIJWEPODJWEIDJLLKASJDKLWEUPJIODJJSKLDADOPIJASKDpajksdioaj");
	// }

	// printf("total mem usage = %zu\n", sizeof(char) * string.capacity);

	// printf("%s\n", string.ptr);

	// string_free(&string);
// }