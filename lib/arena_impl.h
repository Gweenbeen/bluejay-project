// arena_impl.h

struct IntArenaBlock
{
	const int *ptr;
	size_t length;
	size_t capacity;

	struct IntArenaBlock *next;
};

struct IntArena
{
	size_t initial_capacity;
	struct IntArenaBlock *tail;
	struct IntArenaBlock *head;
};

void int_arena_block_make(struct IntArena *self);
void int_arena_block_free(struct IntArena *self);
void int_arena_block_add(struct IntArena *self);
int *int_arena_block_alloc(struct IntArena *self);

void int_arena_init(struct IntArena *self);
void int_arena_free(struct IntArena *self);
void int_arena_push_block(struct IntArena *self);
int *int_arena_alloc(struct IntArena *self);