#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "compiler/ast/node.h"
#include "compiler/lexer/token.h"
#include <string>
#include <cstdint> // For int64_t
#include <utility> // For std::move
#include <vector> // For std::vector
#include <memory> // For std::unique_ptr

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

// Represents a function call expression, e.g., myFunction(arg1, arg2)
class CallExpression : public Expression {
public:
    Token token; // The '(' token
    std::unique_ptr<Expression> function; // Identifier or FunctionLiteral
    std::vector<std::unique_ptr<Expression>> arguments;

    // Constructor takes the token (usually '('), the function expression, and arguments
    CallExpression(Token t, std::unique_ptr<Expression> func)
        : token(std::move(t)), function(std::move(func)) {}

    std::string tokenLiteral() const override { return token.literal; }
    std::string toString() const override {
        std::string out = function->toString() + "(";
        for (size_t i = 0; i < arguments.size(); ++i) {
            out += arguments[i]->toString();
            if (i < arguments.size() - 1) {
                out += ", ";
            }
        }
        out += ")";
        return out;
    }
    void expressionNode() const override {} // Implement dummy marker
};

#endif // EXPRESSION_H
