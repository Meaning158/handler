#pragma once
#include <string>
#include "Token.h"
#include "TokenType.h"

class Token {
public:
    Token() = default;
    Token(const std::string& value, const TokenType& type) : value(value), type(type) {
        pos = quantity;
        ++quantity;
    }
    virtual ~Token() {}

    TokenType getTokenType();
    std::string getTokenValue();
    int getTokenPos() const;
private:
    TokenType type;
    std::string value;
    int pos;
    static inline unsigned quantity{};
};




