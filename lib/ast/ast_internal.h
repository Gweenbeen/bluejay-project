// ast_internal.h

#pragma once

#include <stddef.h>

struct ASTNode;

// ASTNodeList :: Static array of ASTNode
struct ASTNodeList
{
	struct ASTNode **ptr;
	size_t length;
};