// ast_internal.h

#pragma once

#include "array.h"

struct ASTNode;

// ASTList :: Static buffer of ASTNode
struct ASTNodeList
{
	struct ASTNode **ast;
	size_t length;
};

extern void ast_node_list_init(struct ASTNodeList *self);
extern void ast_node_list_free(struct ASTNodeList *self);
extern void ast_node_list_add(struct ASTNodeList *self);
extern void ast_node_list_freeze(struct ASTNodeList *self);