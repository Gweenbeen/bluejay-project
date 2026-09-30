	Array array = {0};
	array_init(&array, sizeof(int));

	int x = 67, y = 99, z = 1054;
	array_push_back(&array, &x);
	array_push_back(&array, &y);
	array_push_back(&array, &z);

	printf("yay! n = %d", *(int*)array_at_clamped(&array, 999));

	array_free(&array);





	
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
		TokenStream tokens = {0};
		token_stream_init(&tokens);

		token_stream_push(&tokens, &(Token){ "salutations realm" });
		token_stream_push(&tokens, &(Token){ "text 1 gjhkgjg" });
		token_stream_push(&tokens, &(Token){ "text 2 jkhkjhgyu" });
		token_stream_push(&tokens, &(Token){ "text 3 fhgfgh" });
		token_stream_push(&tokens, &(Token){ "text 4" });
		token_stream_push(&tokens, &(Token){ "text 5" });
		token_stream_push(&tokens, &(Token){ "text 6" });
		token_stream_push(&tokens, &(Token){ "text 7" });
		token_stream_push(&tokens, &(Token){ "text 8" });
		token_stream_push(&tokens, &(Token){ "text 9" });
		token_stream_push(&tokens, &(Token){ "text 10" });
		token_stream_push(&tokens, &(Token){ "text 11" });
		token_stream_push(&tokens, &(Token){ "text 12" });
		token_stream_push(&tokens, &(Token){ "text 13" });
		token_stream_push(&tokens, &(Token){ "text 14" });

		printf("%s\n", token_stream_at(&tokens, 0)->word);
		printf("%s\n", tokens.ptr[1].word);

		array_for_each(Token*, token, tokens) {
			printf("%s\n", token->word);
		}
		
		return 0;
	}