// parser.h - AST construction

#pragma once

#include "token/token.h"

// Parser :: Constructs AST
struct Parser
{
	struct ASTContext *ast;
	struct ScopeContext *scope;

	struct TokenStream *tokens;
};

static struct ASTNode *parse_program(struct Parser *parser);

// parser_run :: Constructs AST
static void parser_run(struct ASTContext *ast, struct ScopeContext *scope, struct TokenStream *tokens)
{
	// ARRAY_FOR_EACH_PTR (struct Token *, t, tokens) {
		// token_print(t);

	struct Parser self = {0};

	self.ast = ast;
	self.scope = scope;
	self.tokens = tokens;

	self.ast->root = parse_program(&self);
}

static struct ASTNode *parse_program(struct Parser *parser)
{
	// return ast_node_make(parser->ast, AST_UNKNOWN);
	return nullptr;
}