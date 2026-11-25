// threads.h - Thread manager API

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static constexpr size_t DEFAULT_NUM_THREADS = 8;

struct ThreadWork
{
	int value;

	// void (*func)(void *arg);
	// void *arg;

	struct ThreadWork *prev;
	struct ThreadWork *next;
};

struct ThreadPool
{
	// pthread_mutex_t lock;
	// pthread_cond_t notify;

	// pthread_t *threads;
	// size_t num_threads;
	// bool stop;

	struct ThreadWork *first;
	struct ThreadWork *last;
};

static struct ThreadWork *thread_work_make(int value)
{
	struct ThreadWork *self = malloc(sizeof(struct ThreadWork));

	self->value = value;
	self->prev = nullptr;
	self->next = nullptr;

	return self;
}

static void thread_work_add(struct ThreadWork *to, struct ThreadWork *from)
{
	to->next = from;
	from->prev = to;
}

static void thread_pool_init(struct ThreadPool *self)
{
	self->first = nullptr;
	self->last = nullptr;
}

static void thread_pool_free(struct ThreadPool *self)
{
	struct ThreadWork *current = self->first;

	while (current != nullptr)
	{
		struct ThreadWork *next = current->next;

		printf("%d\n", current->value);
		// printf("\t%d\n", current->prev ? current->prev->value : 0);
		// printf("\t%d\n", current->next ? current->next->value : 0);

		free(current);

		current = next;
	}
}

static void thread_pool_push(struct ThreadPool *self, struct ThreadWork *node)
{
	if (self->last == node) {
		return;
	}

	if (self->first == nullptr) {
		self->first = node;
		self->last = self->first;
	} else {
		thread_work_add(self->last, node);
	}

	self->last = node;
}

static struct ThreadWork *thread_pool_pop(struct ThreadPool *self)
{
	struct ThreadWork *node = self->first;

	if (node == nullptr) {
		return nullptr;
	}

	self->first = node->next;

	if (self->first != nullptr) {
		self->first->prev = nullptr;
	} else {
		self->last = nullptr;
	}

	node->prev = nullptr;
	node->next = nullptr;

	return node;
}

void test(void)
{
	struct ThreadWork *worker1 = thread_work_make(15);
	struct ThreadWork *worker2 = thread_work_make(20);
	struct ThreadWork *worker3 = thread_work_make(35);
	struct ThreadWork *worker4 = thread_work_make(50);

	struct ThreadPool pool = {0};
	thread_pool_init(&pool);

	thread_pool_push(&pool, worker1);
	thread_pool_push(&pool, worker2);
	thread_pool_push(&pool, worker3);
	thread_pool_push(&pool, worker4);
	// thread_pool_push(&pool, worker4);

	// for (size_t i = 0; i < 50; ++i) {
		// thread_pool_push(&pool, thread_work_make((i + 1) * 10));
	// }

	free((void *)thread_pool_pop(&pool));

	thread_pool_free(&pool);
}