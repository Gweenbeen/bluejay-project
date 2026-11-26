// expr.h - AST nodes for expressions

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct ExprLiteralInteger
{
	struct ASTNode *token;
};

struct ExprLiteralFloat
{
	struct ASTNode *token;
};

struct ExprLiteralChar
{
	struct ASTNode *token;
};

struct ExprLiteralBoolean
{
	struct ASTNode *token;
};

struct ExprLiteralString
{
	struct ASTNode *token;
};

struct ExprIdentifer
{
	struct ASTNode *token;
};

struct ExprUnary
{
	struct ASTNode *operand;
	struct ASTNode *op;
};

struct ExprBinary
{
	struct ASTNode *left;
	struct ASTNode *right;
	struct ASTNode *op;
};

struct ExprTernary
{
	struct ASTNode *cond;
	struct ASTNode *then_stmt;
	struct ASTNode *else_stmt;
};

struct ExprAssign
{
	struct ASTNode *ident;
	struct ASTNode *expr;
};

struct ExprFunctionCall
{
	struct ASTNode *ident;
	struct ASTNode *parameter_list;
};

struct ExprMember // x.i
{
	struct ASTNode *ident;
	struct ASTNode *member;
};

struct ExprPointerMember // x->i
{
	struct ASTNode *ident;
	struct ASTNode *member;
};

struct ExprNamespaceMember
{
	//
};

struct ExprIndex // a[i]
{
	struct ASTNode *ident;
	struct ASTNode *index;
};

struct ExprCast // (type)i or static_cast(type)
{
	struct ASTNode *type;
};

struct ExprNil // nil(n)
{
	struct ASTNode *expr;
};

struct ExprSizeof
{
	struct ASTNode *ident;
};

struct ExprTypeof
{
	struct ASTNode *ident;
};

struct ExprLength
{
	struct ASTNode *ident;
};

struct ExprReserve
{
	struct ASTNode *expr;
};

struct ExprDelete
{
	struct ASTNode *ident;
};
