// main.c

// #include "driver/compiler.h"
// #include "hash_map.h"

#include "hash.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashMapEntry
{
	const char *key;
	void *value;
	int16_t probe;
};

struct HashMap
{
	struct HashMapEntry *items;
	size_t length;
	size_t capacity;
};

void hash_map_reset(struct HashMap *self) {
	for (size_t i = 0; i < self->capacity; ++i) {
		struct HashMapEntry *cur = &(self->items[i]);

		cur->key = nullptr;
		cur->value = nullptr;
		cur->probe = -1;
	}
}

void hash_map_init(struct HashMap *self)
{
	self->length = 0;
	self->capacity = 8;
	self->items = malloc(sizeof(struct HashMapEntry) * self->capacity);

	hash_map_reset(self);
}

void hash_map_free(struct HashMap *self)
{
	if (self->items != nullptr) {
		free((void *)self->items);
	}
	self->items = nullptr;
}

void hash_map_insert(struct HashMap *self, const char *key, void *value)
{
	struct HashMapEntry e = { .key = key, .value = value };

	uint64_t hash = generate_hash(e.key, strlen(e.key));

	size_t index = hash % self->capacity;

	for (;;) {
		struct HashMapEntry *cur = &(self->items[index]);

		if (cur->value == e.value) {
			return;
		}

		if (cur->probe != -1) {
			index = (index + 1) % self->capacity;
			continue;
		}
	
		self->items[index] = e;
		self->items[index].probe = 0;
	}
	
	++self->length;
}

void *hash_map_search(struct HashMap *self, const char *key)
{
	uint64_t hash = generate_hash(e.key, strlen(e.key));

	size_t index = hash % self->capacity;

	for (;;) {
		struct HashMapEntry *cur = &(self->items[i]);

		if (cur->value == nullptr) {
			continue;
		}

		if (strcmp(cur->key, key) == 0) {
			return cur->value;
		}

		index = (index + 1) % self->capacity;
	}

	return nullptr;
}

int main(void)
{
	struct HashMap numbers = {0};
	hash_map_init(&numbers);

	int a = 10;
	int b = 60;
	int c = 25;

	hash_map_insert(&numbers, "number one", &a);
	hash_map_insert(&numbers, "number two", &b);
	hash_map_insert(&numbers, "number three", &c);
	hash_map_insert(&numbers, "number three", &c);

	// int *number = (int *)hash_map_search(&numbers, "number three ");
	// if (number == nullptr) {
		// printf("Nothing!");
	// } else {
		// printf("Found this number: %d", *number);
	// }

	for (size_t i = 0; i < numbers.capacity; ++i) {
		struct HashMapEntry *cur = &(numbers.items[i]);

		if (cur->value == nullptr) {
			printf("%zu = ---\n", i);
		} else {
			printf("%zu = %d\n", i, *(int *)cur->value);
		}
	}

	hash_map_free(&numbers);

	return 0;
}