#include "common.h"
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_INIT_IMPL(struct__, size__, capacity__)\
struct__->size = size__;\
struct__->length = 0;\
struct__->capacity = capacity__;\
struct__->ptr = malloc(struct__->size * struct__->capacity);\

#define ARRAY_FREE_IMPL(struct__)\
if(struct__->ptr != NULL) free(struct__->ptr)\

#define ARRAY_AT_IMPL(struct__, index)\
&struct__->ptr[index * struct__->size]\

#define ARRAY_GROW_IMPL(T, struct__)\
T* ptr = struct__->ptr; struct__->ptr = malloc(struct__->size * struct__->capacity * 2); \
memcpy(ptr, struct__->ptr, struct__->capacity * struct__->size); \
struct__->capacity *= 2; struct__->ptr = ptr\

#define DEFINE_ARRAY(T, struct__, name__)\
typedef struct struct__\
{\
	T* ptr;\
	size_t size;\
	size_t length;\
	size_t capacity;\
} struct__;\
INLINE void name__##_init(struct__* arr) { ARRAY_INIT_IMPL(arr, sizeof(T), 4); }\
INLINE void name__##_free(struct__* arr) { ARRAY_FREE_IMPL(arr); }\
INLINE T* name__##_pop_back(struct__* arr) { if(arr->length == 0) return NULL; return ARRAY_AT_IMPL(arr, --arr->length); }\

#define DEFINE_ARRAY_AT(T, struct__, name__)\
INLINE T* name__(struct__* arr, size_t index)\
{ \
	if(index > arr->capacity || index < 0) return NULL;\
	return ARRAY_AT_IMPL(arr, index);\
}\

#define DEFINE_ARRAY_PUSH_BACK(T, struct__, name__)\
INLINE void name__(struct__* arr, T* item)\
{\
	if(arr->length > arr->capacity) { ARRAY_GROW_IMPL(T, arr); }\
	memcpy(ARRAY_AT_IMPL(arr, arr->length++), item, arr->size);\
}\

DEFINE_ARRAY(int, ArrayInt, array_int);
DEFINE_ARRAY_AT(int, ArrayInt, array_int_at);
DEFINE_ARRAY_PUSH_BACK(int, ArrayInt, array_int_push_back)


typedef struct Token
{
	const char* word;
	int random_number;
} Token;

DEFINE_ARRAY(Token, TokenStream, token_stream);
DEFINE_ARRAY_AT(Token, TokenStream, token_stream_at);
DEFINE_ARRAY_PUSH_BACK(Token, TokenStream, token_stream_push);

int main(int argc, const char* argv[])
{
	ArrayInt array = {0};
	array_int_init(&array);
	
	int* x = array_int_at(&array, 0); *x = 12389;
	int* y = array_int_at(&array, 1); *y = 67;
	int* z = array_int_at(&array, 2); *z = 500;

	int a = 999;

	array_int_push_back(&array, &a);

	printf("%d", *array_int_at(&array, 0)); // this should print 999

	array_int_free(&array);

	TokenStream tokens = {0};
	token_stream_init(&tokens);

	token_stream_push(&tokens, &(Token){ "hello world" });

	printf("%s", *token_stream_at(&tokens, 0)->word);

	token_stream_free(&tokens);

	return 0;
}