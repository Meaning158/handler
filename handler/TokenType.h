#pragma once

#pragma once
#include <string>
#include "TokenType.h"
class TokenType
{
public:
    TokenType(std::string type_, std::string regex_) : type(type_), regex(regex_)
    {}
    std::string getType();

    std::string getRegex();

private:
    std::string type;
    std::string regex;
};


