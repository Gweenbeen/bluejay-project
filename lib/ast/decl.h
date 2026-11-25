// decl.h - AST nodes for declarations

#pragma once

#include "ast/ast_internal.h"

struct ASTNode;

struct DeclModule {};
struct DeclImport {};
struct DeclExport {};
struct DeclBlock {};
struct DeclFunction {};
struct DeclFunctionProto {};
struct DeclEnum {};
struct DeclEnumProto {};
struct DeclClass {};
struct DeclClassProto {};
struct DeclUnion {};
struct DeclUnionProto {};
struct DeclVariable {};