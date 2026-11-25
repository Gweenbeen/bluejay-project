// expr.h - AST nodes for expressions

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct ExprLiteralInteger {};
struct ExprLiteralFloat {};
struct ExprLiteralChar {};
struct ExprLiteralBoolean {};
struct ExprLiteralString {};
struct ExprIdentifer {};
struct ExprUnary {};
struct ExprBinary {};
struct ExprTernary {};
struct ExprAssign {};
struct ExprFunctionCall {};
struct ExprMember {};
struct ExprPointerMember {};
struct ExprNamespaceMember {};
struct ExprIndex {};
struct ExprCast {};
struct ExprNil {};
struct ExprSizeof {};
struct ExprTypeof {};
struct ExprLength {};
struct ExprReserve {};
struct ExprDestroy {};