// threads.h - Thread manager API

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static constexpr size_t DEFAULT_NUM_THREADS = 8;

struct ThreadWork
{
	int number;

	void (*func)(void *args);
	void *args;
};

struct ThreadPool
{
	struct ThreadWork *threads;
	size_t capacity;
	size_t first;
	size_t last;

	pthread_mutex_t lock;
};

void thread_pool_init(struct ThreadPool *self, size_t capacity)
{
	self->capacity = capacity;

	self->threads = malloc(sizeof(struct ThreadWork) * self->capacity);
	self->first = 0;
	self->last = 0;
}

void thread_pool_free(struct ThreadPool *self)
{
	free(self->threads);

	self->threads = nullptr;
	self->capacity = 0;
}

void thread_pool_push(struct ThreadPool *self, struct ThreadWork *thread)
{
	size_t next = self->last + 1;

	if (next == self->first) {
		return;
	}

	if (next >= self->capacity) {
		next = 0;
	}

	struct ThreadWork t = *thread;

	self->threads[self->last] = t;
	self->last = next;
}

struct ThreadWork *thread_pool_pop(struct ThreadPool *self)
{
	if (self->last == self->first) {
		return nullptr;
	}

	size_t next = self->first + 1;

	if (next >= self->capacity) {
		next = 0;
	}

	self->first = next;
	
	return &(self->threads[self->first]);
}

void test(void)
{
	struct ThreadPool pool = {0};
	thread_pool_init(&pool, 3);

	thread_pool_push(&pool, &(struct ThreadWork){ 15 });
	thread_pool_push(&pool, &(struct ThreadWork){ 30 });
	thread_pool_push(&pool, &(struct ThreadWork){ 45 });
	thread_pool_push(&pool, &(struct ThreadWork){ 60 });

	printf("%d\n", thread_pool_pop(&pool)->number);

	thread_pool_free(&pool);

	return;
}