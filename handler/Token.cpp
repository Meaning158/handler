#pragma once

#include "Token.h"
#include "TokenType.h"


Token::Token(const std::string& value, const TokenType& type, int line, int pos) : value(value), type(type), line(line), pos(pos) {}
TokenType Token::getTokenType() const { return type; }
std::string Token::getTokenValue() const { return value; }
int Token::getTokenPos() const { return pos; }
int Token::getTokenLine() const { return line; }
    

