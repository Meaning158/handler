#pragma once
#include <vector>
#include <iostream>

#include "Token.h"

enum class LeafType {
	file,
	statement,
	console,
	expression,
	atom,
	generic_token
};

class AST {
public:

	AST(Token token, LeafType type, int depth, int leaf_index) : token(token), this_leaf(type), depth(depth), leaf_index(leaf_index) {}

	LeafType this_leaf;
	Token token;
	std::vector<AST> leaves;
	int depth;
	int leaf_index;

};

std::ostream& operator<<(std::ostream& out, const LeafType type);

std::ostream& operator<<(std::ostream& out, const AST& tree);