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
	//Lexer(std::string& code_) :code(code_) { lexAnalysis(code); }
	void lexAnalysis(std::string& code)
	{
			size_t point = 0;
			std::cmatch result;
			std::regex opred;
		for (;point != code.size();) 
		{
			if (code[point] == ' ')
			{
				point++;
				continue;
			}
				for (const auto& [type, regex] : TokenTypeMap)
				{
					opred = "^" + regex;
					std::string str = code.substr(point, code.size());
					if (std::regex_search(str.c_str(), result, opred))
					{
						std::string token = result.str();
						tokenVector.push_back(Token(token, TokenType(type, regex)));
						point += token.size();
						break;
					}
				}
		}
	}
	std::vector<Token> getVector() {
		return tokenVector;
	}

private:
	const std::map<std::string, std::string> TokenTypeMap = {
		{"Number","[0-9]+"},
		{"Variable","[a-zA-Z]+"},
		{"Semicolon","[;]"},
		{"Space","[" "]"},
		{"Assign","[=]"},
		{"Console","console"},
		{"Plus","[+]"},
		{"Minus","[-]"},
		{"Division","[/]"},
		{"Multiplication","[*]"},
		{"Lpar","[(]"},
		{"Rpar","[)]"}
	};
	std::string code;
	std::vector<Token> tokenVector;
};

