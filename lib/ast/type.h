// type.h - AST node and Semantic type

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct TypeBuiltin {};
struct TypeUserDefined {};
struct TypeArray {};
struct TypePointer {};
struct TypeReference {};
struct TypeFunction {};
struct TypeFunctionProto {};