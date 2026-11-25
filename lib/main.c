// main.c - Canonical program entry point

#define NOASSERT

#include "driver/compiler.h"
#include "hash_map.h"
#include <assert.h>

int main(int argc, const char *argv[])
{
	// compiler_run(argc, argv);
	// printf("%s\n", output_path);

	struct HashMap table = {0};
	hash_map_init(&table);

	const char string[] = "hello, world!";
	int number = 80;
	hash_map_insert(&table, string, sizeof(string), &number);
	hash_map_insert(&table, string, sizeof(string), &number);
	hash_map_insert(&table, "hello", 5, &number);

	for (size_t i = 0; i < table.capacity; ++i) {
		struct HashMapEntry *e = &(table.entries[i]);

		if (e->key == nullptr) {
			printf("empty.\n");
		} else {
			printf("%s %d\n", table.entries[i].key, *(int *)table.entries[i].value);
		}
	}

	hash_map_free(&table);

	return 0;
}