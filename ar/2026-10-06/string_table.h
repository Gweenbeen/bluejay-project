// Copyright (c) 2026 Justin Wallace
// string_table.h - Hash map for strings

#pragma once

#include "common.h"

// StringTableEntry :: StringTable entry
typedef struct StringTableEntry
{
	StringView key;
	uint8_t* value;
	int16_t probe_distance;
	uint8_t small_hash;
} StringTableEntry;

// StringTable :: StringTable header
typedef struct StringTable
{
	StringTableEntry* entries;
	size_t length;
	size_t capacity;

	alignas(max_align_t) uint8_t inline_memory[16];
} StringTable;

// string_table_init :: Initalizes an instance of StringTable
INLINE void string_table_init(StringTable* string_table)
{
	string_table->length = 0;
	string_table->capacity = 4;

	string_table->entries = malloc(string_table->capacity * sizeof(StringTableEntry));
}

// string_table_free :: Releases an instance of StringTable
INLINE void string_table_free(StringTable* string_table)
{
	if(string_table == NULL) {
		return;
	}

	if(string_table->entries != NULL) {
		free(string_table->entries);
	}

	string_table->entries = NULL;
	string_table->length = 0;
	string_table->capacity = 0;
}

// string_table_rehash :: Reinserts all elements in StringTable
INLINE void string_table_rehash(StringTable* string_table)
{
	for(size_t i = 0; i < string_table->length; i++) {
		//
	}
}

// string_table_rehash :: Zeroes all elements in StringTable
INLINE void string_table_reset(StringTable* string_table)
{
	for(size_t i = 0; i < string_table->length; i++) {
		StringTableEntry* entry = &(string_table->entries)[i];
		entry->key.ptr = NULL;
		entry->key.length = 0;
		entry->value = NULL;
		entry->probe_distance = -1;
		entry->small_hash = 0;
	}
}

// string_table_resize :: Resizes the length of StringTable. Only allocates if the new length is
// larger than the original length
INLINE void string_table_resize(StringTable* string_table, size_t new_length)
{
	if(new_length > string_table->length) {
		string_table->entries = realloc(string_table->entries, new_length * sizeof(StringTableEntry));
	}

	string_table->length = new_length;
}

