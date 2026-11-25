int main(int argc, const char* argv[])
{
	HashMap phone_book = {0};

	hash_map_init(&phone_book, 32);

	hash_map_insert(&phone_book, "Abagail", "617-229-2359");
	hash_map_insert(&phone_book, "Bobby", "617-359-3945");
	hash_map_insert(&phone_book, "Claire", "617-359-3945");
	hash_map_insert(&phone_book, "Daniel", "617-359-3945");
	hash_map_insert(&phone_book, "Elizabeth", "617-359-3945");
	hash_map_insert(&phone_book, "Frank", "617-359-3945");
	hash_map_insert(&phone_book, "Gabriel", "617-359-3945");
	hash_map_insert(&phone_book, "Howard", "617-359-3945");
	hash_map_insert(&phone_book, "Issac", "617-359-3945");
	hash_map_insert(&phone_book, "James", "617-359-3945");
	hash_map_insert(&phone_book, "Keith", "617-359-3945");
	hash_map_insert(&phone_book, "Louis", "617-359-3945");
	hash_map_insert(&phone_book, "Mabel", "617-359-3945");
	hash_map_insert(&phone_book, "Nathan", "617-359-3945");
	hash_map_insert(&phone_book, "Offred", "617-359-3945");
	hash_map_insert(&phone_book, "Pascal", "617-359-3945");
	hash_map_insert(&phone_book, "Quinn", "617-359-3945");
	hash_map_insert(&phone_book, "Rachel", "617-359-3945");
	hash_map_insert(&phone_book, "Spiderman", "617-359-3945");
	hash_map_insert(&phone_book, "Thomas", "617-359-3945");
	hash_map_insert(&phone_book, "Urel", "617-359-3945");
	hash_map_insert(&phone_book, "Victor", "617-359-3945");
	hash_map_insert(&phone_book, "William", "617-359-3945");
	hash_map_insert(&phone_book, "Xavier", "617-359-3945");
	hash_map_insert(&phone_book, "Yung", "617-359-3945");
	hash_map_insert(&phone_book, "Zachary", "617-359-3945");

	const char* entry = hash_map_find(&phone_book, "Xavier");

	printf("%s\n", entry);

	hash_map_free(&phone_book);



	printf("woop woop\n");
	return 0;
}

int main(int argc, const char *argv[])
{
	struct HashTable numbers = {0};
	hash_table_init(&numbers, 16);

	int x = 50;

	hash_table_insert(&numbers, "some key", &x);

	for (size_t i = 0; i < numbers.capacity; ++i) {
		struct HashTableEntry *cur = &(numbers.entries)[i];
		if (cur->value == nullptr) {
			printf("[%zu] ---\n", i);
		} else {
			printf("[%zu] %s : %d\n", i, cur->key, cur->value);
		}
	}


	hash_table_free(&numbers);
	return 0;
	return compiler_run(argc, argv);
}