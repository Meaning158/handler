#pragma once
#include "TokenType.h"
#include "Token.h"
#include <vector>
#include <iostream>
#include <map>
#include <regex>
#include <algorithm>

class Lexer
{
public:
	std::vector<Token> lexAnalysis(std::string& code);

private:
	const std::map<TokenType, std::string> TokenTypeMap = {
		{TokenType::Console,"console"},
		{TokenType::Number,"[0-9]+"},
		{TokenType::Variable,"[a-zA-Z]+"},
		{TokenType::Semicolon,"[;]"},
		{TokenType::Assign,"[=]"},
		{TokenType::Plus,"[+]"},
		{TokenType::Minus,"[-]"},
		{TokenType::Division,"[/]"},
		{TokenType::Multiplication,"[*]"},
		{TokenType::Lpar,"[(]"},
		{TokenType::Rpar,"[)]"}
	};
};

