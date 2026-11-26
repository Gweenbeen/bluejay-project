// decl.h - AST nodes for declarations

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct DeclModule
{
	struct ASTNode *ident;
};

struct DeclImport
{
	struct ASTNode *path;
};

struct DeclExport
{
	struct ASTNode *function;
};

struct DeclBlock
{
	struct ASTNodeList items;
};

struct DeclFunction
{
	struct ASTNode *signature;
};

struct DeclFunctionProto
{
	struct ASTNode *signature;
};

struct DeclEnum
{
	struct ASTNode *ident;
	struct ASTNode *body;
};

struct DeclEnumProto
{
	struct ASTNode *ident;
};

struct DeclClass
{
	struct ASTNode *ident;
	struct ASTNode *body;
};

struct DeclClassProto
{
	struct ASTNode *ident;
};

struct DeclUnion
{
	struct ASTNode *ident;
	struct ASTNode *body;
};

struct DeclUnionProto
{
	struct ASTNode *ident;
};

struct DeclVariable
{
	struct ASTNode *type;
	struct ASTNode *ident;
	struct ASTNode *expr;
};