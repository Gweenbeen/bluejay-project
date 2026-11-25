// auxiliary - Auxiliary AST nodes

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;
struct Token;

struct Program
{
	struct ASTNodeList items;
};

struct Identifier
{
	struct Token *token;
};

struct Path
{
	struct ASTNodeList items;
};

struct FunctionSignature
{
	struct ASTNode *ident;
	struct ASTNode *parameters;
	struct ASTNode *return_type;
};

struct ClassSignature
{
	struct ASTNode *ident;
	struct ASTNode *parent;
	struct ASTNode *generics;
};

struct EnumSignature
{
	struct ASTNode *ident;
};

struct Argument
{
	struct ASTNode *value;
};

struct ArgumentList
{
	struct ASTNodeList items;
};

struct Parameter
{
	struct ASTNode *ident;
	struct ASTNode *value;
};

struct ParameterList
{
	struct ASTNodeList items;
};

struct Initializer
{
	struct ASTNode *value;
};

struct InitializerTag
{
	struct ASTNode *ident;
	struct ASTNode *value;
};

struct InitializerIndex
{
	struct ASTNode *index;
	struct ASTNode *value;
};

struct InitializerList
{
	struct ASTNodeList items;
};

struct GenericArgument
{
	struct ASTNode *type;
};

struct GenericArgumentList
{
	struct ASTNodeList items;
};

struct Modifier {};
struct Qualifier {};
struct Designator {};
struct Field {};