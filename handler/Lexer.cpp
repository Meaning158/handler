#include "Lexer.h"

std::vector<Token> Lexer::lexAnalysis(std::string& code)
{
	std::vector<Token> tokenVector;
	size_t point = 0;
	int line = 1;
	int pos = 0;
	std::cmatch result;
	std::regex opred;
	for (; point != code.size();)
	{
		++pos;
		if (code[point] == ' ')
		{
			++point;
			continue;
		}
		if (code[point] == '\n')
		{
			++point;
			pos = 1;
			++line;
			continue;
		}
		for (const auto& [type, regex] : TokenTypeMap)
		{
			opred = "^" + regex;
			std::string str = code.substr(point, code.size());
			if (std::regex_search(str.c_str(), result, opred))
			{
				std::string token = result.str();
				tokenVector.push_back(Token(token, type, line, pos));
				point += token.size();
				break;
			}
		}
	}
	return tokenVector;
}

std::ostream& operator<<(std::ostream& out, const TokenType& type)
{
	switch (type)
	{
	case TokenType::Number: out << "Number"; break;
	case TokenType::Variable: out << "Variable"; break;
	case TokenType::Semicolon: out << "Semicolon"; break;
	case TokenType::Assign: out << "Assign"; break;
	case TokenType::Console: out << "Console"; break;
	case TokenType::Plus: out << "Plus"; break;
	case TokenType::Minus: out << "Minus"; break;
	case TokenType::Division: out << "Division"; break;
	case TokenType::Multiplication: out << "Multiplication"; break;
	case TokenType::Lpar: out << "Lpar"; break;
	case TokenType::Rpar: out << "Rpar"; break;
	case TokenType::Generic: out << "Generic"; break;
	default:
		break;
	}
	return out;
}