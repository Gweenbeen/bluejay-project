// hash_map.h

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct HashMapEntry
{
	const char *key;
	size_t length;
	void *value;
};

struct HashMap
{
	struct HashMapEntry *entries;
	size_t length;
	size_t capacity;
};

void hash_map_init(struct HashMap *self)
{
	self->length = 0;
	self->capacity = 32;

	self->entries = malloc(self->capacity * sizeof(struct HashMapEntry));

	for (size_t i = 0; i < self->capacity; ++i) {
		self->entries[i].key = nullptr;
	}
}

void hash_map_free(struct HashMap *self)
{
	if (self->entries != nullptr) {
		free(self->entries);
	}

	self->entries = nullptr;
	self->length = 0;
	self->capacity = 0;
}

void *hash_map_at(struct HashMap *self, size_t index)
{
	return (void *)&(self->entries[index]);
}

void hash_map_insert(struct HashMap *self, const char *key, size_t length, void *value)
{
	struct HashMapEntry e = {
		.key = key,
		.length = length,
		.value = value,
	};

	self->entries[self->length] = e;
	++self->length;
}

void *hash_map_find(struct HashMap *self)
{
	return nullptr;
}
