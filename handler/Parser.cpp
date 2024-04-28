#include "Parser.h"

AST Parser::GenerateAST(std::vector<Token>& tokens)
{
    auto l = AST(Token("Program", TokenType::Generic, 0, 0), LeafType::file, 0, 0);
    auto iter = tokens.begin();
    int index = 0;
    while (iter != tokens.end())
    {
        std::vector<Token>::iterator previous_iter = iter;
        AST statement = get_statement(iter, tokens, 1, index);
        if (iter == previous_iter) break;
        l.leaves.push_back(statement);
        ++index;
    }
    
    return l;
}

AST Parser::get_statement(std::vector<Token>::iterator& from, std::vector<Token>& tokens, int depth, int leaf_index)
{
    AST l = AST(Token("Statement", TokenType::Generic, from->getTokenLine(), from->getTokenPos()), LeafType::statement, depth, leaf_index);
    std::vector<Token>::iterator iter = from;
    AST result = get_console(iter, depth + 1, 0);
    if (iter != from)
        l.leaves.push_back(result);
    else
    {
        result = get_expression(iter, depth + 1, 0);
        if (iter == from) return l;
        l.leaves.push_back(result);
    }
    std::vector<Token>::iterator prev = iter;
    if (iter == tokens.end() || ((result = get_generic(iter, TokenType::Semicolon, depth + 1, 1)).this_leaf == LeafType::generic_token && iter == prev))
        throw std::runtime_error(
            std::format("Missing semicolon at ({},{}): '{}'", from->getTokenLine(), from->getTokenPos(), from->getTokenValue()));
    l.leaves.push_back(result);
    from = iter;
    return l;	
}

AST Parser::get_console(std::vector<Token>::iterator& from, int depth, int leaf_index)
{
    AST l = AST(Token("Console", TokenType::Generic, from->getTokenLine(), from->getTokenPos()), LeafType::console, depth, leaf_index);
    std::vector<Token>::iterator iter = from;
    AST result = get_generic(iter, TokenType::Console, depth + 1, 0);
    if (iter == from)
        return l;
    l.leaves.push_back(result);
    std::vector<Token>::iterator prev = iter;
    result = get_expression(iter, depth + 1, 1);
    if (iter == prev)
        throw std::runtime_error(
            std::format("Expected expression at ({},{}): '{}'", from->getTokenLine(), from->getTokenPos(), from->getTokenValue()));
    l.leaves.push_back(result);
    from = iter;
    return l;
}

AST Parser::get_binary_op(std::vector<Token>::iterator& from, std::string name, TokenType op, int depth, int leaf_index)
{
    AST l = AST(Token(name, TokenType::Generic, from->getTokenLine(), from->getTokenPos()), LeafType::expression, depth, 0);
    std::vector<Token>::iterator iter = from;
    std::vector<Token>::iterator prev = iter;
    AST result = get_generic(iter, op, depth, leaf_index);
    if (iter == prev)
        return l;
    l.leaves.push_back(result);
    prev = iter;
    result = get_expression(iter, depth, leaf_index + 1);
    if (iter == prev)
        throw std::runtime_error(
            std::format("Expected expression at ({},{}): '{}'", from->getTokenLine(), from->getTokenPos(), from->getTokenValue()));
    l.leaves.push_back(result);
    from = iter;
    return l;
}

AST Parser::get_expression(std::vector<Token>::iterator& from, int depth, int leaf_index)
{
    AST l = AST(Token("Expression", TokenType::Generic, from->getTokenLine(), from->getTokenPos()), LeafType::expression, depth, leaf_index);
    std::vector<Token>::iterator iter = from;
    std::vector<Token>::iterator prev = iter;
    AST result = get_generic(iter, TokenType::Lpar, depth + 1, 0);
    if (iter != from)
    {
        l.leaves.push_back(result);
        prev = iter;
        result = get_expression(iter, depth + 1, 1);
        if (iter == prev)
            throw std::runtime_error(
                std::format("Expected expression at ({},{}): '{}'", from->getTokenLine(), from->getTokenPos(), from->getTokenValue()));
        l.leaves.push_back(result);
        prev = iter;
        result = get_generic(iter, TokenType::Rpar, depth + 1, 2);
        if (iter == prev)
            throw std::runtime_error(
                std::format("Unpaired bracket at ({},{}): '{}'", from->getTokenLine(), from->getTokenPos(), from->getTokenValue()));
        l.leaves.push_back(result);

        prev = iter;
        result = get_binary_op(iter, "Assignment", TokenType::Assign, depth + 1, 3);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Multiplication", TokenType::Multiplication, depth + 1, 3);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Division", TokenType::Division, depth + 1, 3);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Addition", TokenType::Plus, depth + 1, 3);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Subtraction", TokenType::Minus, depth + 1, 3);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }

        from = iter;
        return l;
    }
    result = get_atom(iter, depth + 1, 0);
    if (iter != from)
    {
        l.leaves.push_back(result);
        prev = iter;
        result = get_binary_op(iter, "Assignment", TokenType::Assign, depth + 1, 1);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Multiplication", TokenType::Multiplication, depth + 1, 1);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Division", TokenType::Division, depth + 1, 1);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Addition", TokenType::Plus, depth + 1, 1);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        result = get_binary_op(iter, "Subtraction", TokenType::Minus, depth + 1, 1);
        if (iter != prev)
        {
            l.leaves.push_back(result.leaves[0]);
            l.leaves.push_back(result.leaves[1]);
            from = iter;
            return l;
        }
        from = iter;
        return l;
    }
    
    return l;
}

AST Parser::get_atom(std::vector<Token>::iterator& from, int depth, int leaf_index)
{
    AST l = AST(Token("Atom", TokenType::Generic, from->getTokenLine(), from->getTokenPos()), LeafType::atom, depth, leaf_index);
    std::vector<Token>::iterator iter = from;
    AST result = get_generic(iter, TokenType::Variable, depth + 1, 0);
    if (iter != from)
        l.leaves.push_back(result);
    else
    {
        result = get_generic(iter, TokenType::Number, depth + 1, 0);
        if (iter == from)
            return l;
        l.leaves.push_back(result);
    }
    from = iter;
    return l;
}

AST Parser::get_generic(std::vector<Token>::iterator& from, TokenType type, int depth, int leaf_index)
{
    AST result = AST(*from, LeafType::generic_token, depth, leaf_index);
    if (from->getTokenType() == type) from++;
    return result;
}

std::ostream& operator<<(std::ostream& out, const LeafType type)
{
    switch (type)
    {
    case LeafType::file: out << "File node"; break;
    case LeafType::statement: out << "Statement node"; break;
    case LeafType::console: out << "Console node"; break;
    case LeafType::expression: out << "Expression node"; break;
    case LeafType::atom: out << "Value node"; break;
    case LeafType::generic_token: out << "Generic node"; break;
    default:
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const AST& tree)
{
    out << "\"" << tree.this_leaf << tree.leaf_index
        << "\" : {\"Depth\": \"" << tree.depth
        << "\", \"Value\" : \"" << tree.token.getTokenValue()
        << "\", \"Type\" : \"" << tree.token.getTokenType()
        << "\", \"Leaves\" : {";
    for (auto& each : tree.leaves)
        out << "  " << each << ", ";
    out << "}}";
    return out;
}