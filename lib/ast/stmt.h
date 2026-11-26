// stmt.h - AST nodes for statements

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct StmtBlock
{
	struct ASTNode *body;
};

struct StmtDecl
{
	struct ASTNode *decl;
};

struct StmtExpr
{
	struct ASTNode *expr;
};

struct StmtIf
{
	struct ASTNode *cond;
	struct ASTNode *body;
};

struct StmtElif
{
	struct ASTNode *cond;
	struct ASTNode *body;
};

struct StmtElse
{
	struct ASTNode *body;
};

struct StmtWhile
{
	struct ASTNode *cond;
	struct ASTNode *body;
};

struct StmtDoWhile
{
	struct ASTNode *cond;
	struct ASTNode *body;
};

struct StmtFor
{
	struct ASTNode *left;
	struct ASTNode *middle;
	struct ASTNode *right;
	struct ASTNode *body;
};

struct StmtForUnbounded
{
	struct ASTNodeList *decl;
	struct ASTNode *body;
};

struct StmtForIn
{
	struct ASTNode *type;
	struct ASTNode *ident;
	struct ASTNode *body;
};

struct StmtTry
{
	//
};

struct StmtLoop
{
	struct ASTNode *body;
};

struct StmtReturn
{
	struct ASTNode *expr;
};

struct StmtBreak
{
	//
};

struct StmtContinue
{
	//
};

struct StmtGoto
{
	struct ASTNode *ident;
};

struct StmtIndirectGoto
{
	//
};

struct StmtLabel
{
	struct ASTNode *ident;
};

struct StmtBuiltinLabel
{
	struct ASTNode *ident;
};


struct StmtAssert
{
	struct ASTNode *expr;
};

struct StmtAssertMessage
{
	struct ASTNode *expr;
	struct ASTNode *message;
};

struct StmtStaticAssert
{
	struct ASTNode *expr;
};

struct StmtStaticAssertMessage
{
	struct ASTNode *expr;
	struct ASTNode *message;
};

struct StmtAssume
{
	struct ASTNode *expr;
};