// tests.h - Testing API

#pragma once

// Test :: Single test module
struct Test
{
	const char *name;
	const char *description;

	void (*setup_impl)(void);
	void (*teardown_impl)(void);
};

// Tests :: Header for tests
struct Tests
{
	DEFINE_ARRAY_HEADER(struct Test);

	size_t num_tests;
	size_t num_pass;
	size_t num_fail;
};


