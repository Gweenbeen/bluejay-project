// stmt.h - AST nodes for statements

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct StmtBlock {};
struct StmtDecl {};
struct StmtExpr {};
struct StmtIf {};
struct StmtElif {};
struct StmtElse {};
struct StmtWhile {};
struct StmtDoWhile {};
struct StmtFor {};
struct StmtForIn {};
struct StmtTry {};
struct StmtLoop {};
struct StmtReturn {};
struct StmtBreak {};
struct StmtContinue {};
struct StmtGoto {};
struct StmtIndirectGoto {};
struct StmtLabel {};
struct StmtAssert {};
