#pragma once
#include <vector>
#include <stdexcept>
#include <format>
#include "Token.h"
#include "ASTree.h"

class Parser
{
public:

	AST GenerateAST(std::vector<Token>& tokens);

private:

	AST get_statement(std::vector<Token>::iterator& from, std::vector<Token>& tokens, int depth, int leaf_index);
	AST get_console(std::vector<Token>::iterator& from, int depth, int leaf_index);
	AST get_binary_op(std::vector<Token>::iterator& from, std::string name, TokenType op, int depth, int leaf_index);
	AST get_expression(std::vector<Token>::iterator& from, int depth, int leaf_index);
	AST get_atom(std::vector<Token>::iterator& from, int depth, int leaf_index);
	AST get_generic(std::vector<Token>::iterator& from, TokenType type, int depth, int leaf_index);

};

