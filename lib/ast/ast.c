// ast.c - From "ast.h"

#include "ast/ast.h"
#include "bump_arena.h"

extern void ast_context_init(struct ASTContext *self)
{
	self->root = nullptr;

	bump_arena_init(&self->arena, 800);
}

extern void ast_context_free(struct ASTContext *self)
{
	bump_arena_free(&self->arena);
}