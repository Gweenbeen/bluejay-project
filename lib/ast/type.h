// type.h - AST node and Semantic type

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct TypeBuiltin
{
	struct ASTNode *type;
};

struct TypeUserDefined
{
	struct ASTNode *ident;
};

struct TypeArray
{
	struct ASTNode *type;
	struct ASTNode *size;
};

struct TypePointer
{
	struct ASTNode *type;
};

struct TypeReference
{
	struct ASTNode *type;
};

struct TypeFunction
{
	struct ASTNode *signature;
};

struct TypeFunctionProto
{
	struct ASTNode *signature;
};