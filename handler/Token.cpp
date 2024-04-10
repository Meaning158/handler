#pragma once

#include "Token.h"
#include "TokenType.h"


TokenType Token::getTokenType() { return type; }
std::string Token::getTokenValue() { return value; }
int Token::getTokenPos() const { return pos; }
    

