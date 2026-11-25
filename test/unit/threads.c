// main.c

#include "stringt.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

constexpr size_t ITERATIONS = 100000;
constexpr size_t NUM_THREADS = 16;

static size_t counter = 0;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *task(void *arg) {
	size_t local_counter = 0;
	for (size_t i = 0; i < ITERATIONS; ++i) {
		++local_counter;
	}

	return &local_counter;
}

void *function(void *arg)
{
	printf("Running thread #%zu\n", *(size_t *)args);

	int c = *(int *)task(nullptr);	

	// pthread_mutex_lock(&counter_mutex);
	counter += c;
	// pthread_mutex_unlock(&counter_mutex);

	return nullptr;
}

int main(int argc, const char *argv[])
{
	pthread_t threads[NUM_THREADS];

	for (size_t i = 0; i < NUM_THREADS; ++i) {
		pthread_create(&threads[i], nullptr, function(&i), nullptr);
	}

	for (size_t i = 0; i < NUM_THREADS; ++i) {
		pthread_join(threads[i], nullptr);
	}
	
	printf("Got: %zu\nExpected %zu\n", counter, ITERATIONS * NUM_THREADS);

	pthread_mutex_destroy(&counter_mutex);
	return 0;
}