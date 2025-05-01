#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "compiler/ast/node.h"
#include "compiler/lexer/token.h"
#include <string>
#include <cstdint> // For int64_t
#include <utility> // For std::move

// Base class for all expression nodes in the AST
class Expression : public Node {
public:
    // Pure virtual function to mark this as an Expression node type.
    // This helps in differentiating Statements from Expressions if needed later.
    virtual void expressionNode() const = 0;
};

// Represents an integer literal expression, e.g., 5, 100
class IntegerLiteral : public Expression {
public:
    Token token; // The TokenType::IntegerLiteral token
    int64_t value;

    IntegerLiteral(Token t, int64_t val) : token(std::move(t)), value(val) {}

    std::string tokenLiteral() const override { return token.literal; }
    std::string toString() const override { return token.literal; }
    void expressionNode() const override {} // Implement dummy marker
};

// Represents a floating-point literal expression, e.g., 3.14, 0.5
class FloatLiteral : public Expression {
public:
    Token token; // The TokenType::FloatLiteral token
    double value;

    FloatLiteral(Token t, double val) : token(std::move(t)), value(val) {}

    std::string tokenLiteral() const override { return token.literal; }
    std::string toString() const override { return token.literal; }
    void expressionNode() const override {} // Implement dummy marker
};

// Represents a string literal expression, e.g., "hello"
class StringLiteral : public Expression {
public:
    Token token; // The TokenType::StringLiteral token
    std::string value; // The actual string content (without quotes)

    StringLiteral(Token t, std::string val) : token(std::move(t)), value(std::move(val)) {}

    std::string tokenLiteral() const override { return token.literal; }
    // toString might include quotes for clarity, matching token literal
    std::string toString() const override { return token.literal; }
    void expressionNode() const override {} // Implement dummy marker
};

// Represents an identifier expression, e.g., myVariable, x
class Identifier : public Expression {
public:
    Token token; // The TokenType::Identifier token
    std::string value; // The name of the identifier

    Identifier(Token t, std::string val) : token(std::move(t)), value(std::move(val)) {}

    std::string tokenLiteral() const override { return token.literal; }
    // toString should represent the identifier's name
    std::string toString() const override { return value; }
    void expressionNode() const override {} // Implement dummy marker
};

#endif // EXPRESSION_H
