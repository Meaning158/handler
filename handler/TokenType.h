#pragma once
#include <iostream>

enum class TokenType {
	Console,
	Number,
	Variable,
	Semicolon,
	Assign,
	Plus,
	Minus,
	Division,
	Multiplication,
	Lpar,
	Rpar,
	Generic
};

std::ostream& operator<<(std::ostream& out, const TokenType& type);