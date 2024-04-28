#pragma once
#include <string>
#include "Token.h"
#include "TokenType.h"

class Token {
public:
    Token() = default;
    Token(const std::string& value, const TokenType& type, int line, int pos);
    virtual ~Token() {}

    TokenType getTokenType() const;
    std::string getTokenValue() const;
    int getTokenPos() const;
    int getTokenLine() const;
private:
    TokenType type;
    std::string value;
    int pos;
    int line;
};




