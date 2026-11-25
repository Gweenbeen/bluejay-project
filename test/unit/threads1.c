// main.c

#include "threads.h"

static constexpr size_t max_threads = 5;
static constexpr size_t iterations = 100000;
static  size_t count = 0;

void *job(void *args)
{
	for (size_t i = 0; i < iterations; ++i) {
		++count;
	}

	return nullptr;
}

int main(int argc, const char *argv[])
{
	pthread_t threads[max_threads] = {0};

	for (size_t i = 0; i < max_threads; ++i) {
		pthread_create(&threads[i], nullptr, job, nullptr);
	}

	for (size_t i = 0; i < max_threads; ++i) {
		pthread_join(threads[i], nullptr);
	}

	printf("expected: %zu\nactual: %zu\n", iterations * max_threads, count);

	// test();
	return 0;
}