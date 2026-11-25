// ast.h - AST nodes

#pragma once

#include "ast/ast_internal.h"
#include "ast/auxiliary.h"
#include "ast/decl.h"
#include "ast/expr.h"
#include "ast/stmt.h"
#include "ast/type.h"
#include "bump_arena.h"

// ASTNodeKind :: AST node type
enum ASTNodeKind 
{
	AST_PROGRAM,
	AST_UNKNOWN,
};

// ASTNode :: AST node to be used for parsing
struct ASTNode
{
	enum ASTNodeKind kind;

	union
	{
		struct Program program;
		struct Identifier identifier;
		struct Path path;
		struct FunctionSignature function_signature;
		struct ClassSignature class_signature;
		struct EnumSignature enum_signature;
		struct Argument argument;
		struct ArgumentList argument_list;
		struct Parameter parameter;
		struct ParameterList parameter_list;
		struct Initializer initializer;
		struct InitializerTag initializer_tag;
		struct InitializerIndex initializer_index;
		struct InitializerList initializer_list;
		struct GenericArgument generic_argument;
		struct GenericArgumentList generic_argument_list;

		struct DeclModule decl_module;
		struct DeclImport decl_import;
		struct DeclExport decl_export;
		struct DeclFunction decl_function;
		struct DeclFunctionProto decl_function_proto;
		struct DeclEnum decl_enum;
		struct DeclEnumProto decl_enum_proto;
		struct DeclClass decl_class;
		struct DeclClassProto decl_class_proto;
		struct DeclUnion decl_union;
		struct DeclUnionProto decl_union_proto;
		struct DeclVariable decl_variable;

		struct ExprLiteralInteger expr_literal_integer;
		struct ExprLiteralFloat expr_literal_float;
		struct ExprLiteralChar expr_literal_char;
		struct ExprLiteralBoolean expr_literal_boolean;
		struct ExprLiteralString expr_literal_string;
		struct ExprIdentifer expr_identifer;
		struct ExprUnary expr_unary;
		struct ExprBinary expr_binary;
		struct ExprTernary expr_ternary;
		struct ExprAssign expr_assign;
		struct ExprFunctionCall expr_function_call;
		struct ExprMember expr_member;
		struct ExprPointerMember expr_pointer_member;
		struct ExprNamespaceMember expr_namespace_member;
		struct ExprIndex expr_index;
		struct ExprCast expr_cast;
		struct ExprNil expr_nil;
		struct ExprSizeof expr_sizeof;
		struct ExprTypeof expr_typeof;
		struct ExprLength expr_length;
		struct ExprReserve expr_reserve;
		struct ExprDestroy expr_destroy;

		struct StmtBlock stmt_block;
		struct StmtDecl stmt_decl;
		struct StmtExpr stmt_expr;
		struct StmtIf stmt_if;
		struct StmtElif stmt_elif;
		struct StmtElse stmt_else;
		struct StmtWhile stmt_while;
		struct StmtDoWhile stmt_do_while;
		struct StmtFor stmt_for;
		struct StmtForIn stmt_for_in;
		struct StmtTry stmt_try;
		struct StmtLoop stmt_loop;
		struct StmtReturn stmt_return;
		struct StmtBreak stmt_break;
		struct StmtContinue stmt_continue;
		struct StmtGoto stmt_goto;
		struct StmtIndirectGoto stmt_indirect_goto;
		struct StmtLabel stmt_label;
		struct StmtAssert stmt_assert;

		struct TypeBuiltin type_builtin;
		struct TypeUserDefined type_user_defined;
		struct TypeArray type_array;
		struct TypePointer type_pointer;
		struct TypeReference type_reference;
		struct TypeFunction type_function;
		struct TypeFunctionProto type_function_proto;
	};
};

// ASTContext :: Tracks AST
struct ASTContext
{
	struct BumpArena arena;

	struct ASTNode *root;
};

extern void ast_context_init(struct ASTContext *self);
extern void ast_context_free(struct ASTContext *self);

static void ast_node_print_tree(struct ASTNode *self, size_t depth)
{
	if (self == nullptr) {
		return;
	}

	for (size_t i = 0; i < depth; ++i) {
		printf("  ");
	}

	switch(self->kind)
	{
	case AST_PROGRAM:
		printf("Program\n");
		break;
	default:
		printf("Unknown node\n");
		break;
	}
}

static struct ASTNode *ast_node_make(struct ASTContext *context, enum ASTNodeKind kind)
{
	struct ASTNode *node = bump_arena_alloc(&context->arena, sizeof(struct ASTNode));

	node->kind = kind;

	return node;
}

extern struct ASTNode *ast_node_make_program(struct ASTContext *context);
extern struct ASTNode *ast_node_make_identifier(struct ASTContext *context);
extern struct ASTNode *ast_node_make_path(struct ASTContext *context);
extern struct ASTNode *ast_node_make_function_signature(struct ASTContext *context);
extern struct ASTNode *ast_node_make_class_signature(struct ASTContext *context);
extern struct ASTNode *ast_node_make_enum_signature(struct ASTContext *context);
extern struct ASTNode *ast_node_make_argument(struct ASTContext *context);
extern struct ASTNode *ast_node_make_argument_list(struct ASTContext *context);
extern struct ASTNode *ast_node_make_parameter(struct ASTContext *context);
extern struct ASTNode *ast_node_make_parameter_list(struct ASTContext *context);
extern struct ASTNode *ast_node_make_initializer(struct ASTContext *context);
extern struct ASTNode *ast_node_make_initializer_tag(struct ASTContext *context);
extern struct ASTNode *ast_node_make_initializer_index(struct ASTContext *context);
extern struct ASTNode *ast_node_make_initializer_list(struct ASTContext *context);
extern struct ASTNode *ast_node_make_generic_argument(struct ASTContext *context);
extern struct ASTNode *ast_node_make_generic_argument_list(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_module(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_import(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_export(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_function(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_function_proto(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_enum(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_enum_proto(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_class(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_class_proto(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_union(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_union_proto(struct ASTContext *context);
extern struct ASTNode *ast_node_make_decl_variable(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_literal_integer(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_literal_float(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_literal_char(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_literal_boolean(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_literal_string(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_identifer(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_unary(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_binary(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_ternary(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_assign(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_function_call(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_member(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_pointer_member(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_namespace_member(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_index(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_cast(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_nil(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_sizeof(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_typeof(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_length(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_reserve(struct ASTContext *context);
extern struct ASTNode *ast_node_make_expr_destroy(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_block(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_decl(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_expr(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_if(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_elif(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_else(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_while(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_do_while(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_for(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_for_in(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_try(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_loop(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_return(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_break(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_continue(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_goto(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_indirect_goto(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_label(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_assume(struct ASTContext *context);
extern struct ASTNode *ast_node_make_stmt_assert(struct ASTContext *context);
extern struct ASTNode *ast_node_make_type_builtin(struct ASTContext *context);
extern struct ASTNode *ast_node_make_type_user_defined(struct ASTContext *context);
extern struct ASTNode *ast_node_make_type_array(struct ASTContext *context);
extern struct ASTNode *ast_node_make_type_pointer(struct ASTContext *context);
extern struct ASTNode *ast_node_make_type_reference(struct ASTContext *context);
extern struct ASTNode *ast_node_make_type_function(struct ASTContext *context);
extern struct ASTNode *ast_node_make_type_function_proto(struct ASTContext *context);