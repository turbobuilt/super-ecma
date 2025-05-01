#ifndef STATEMENT_H
#define STATEMENT_H

#include "compiler/ast/node.h"
#include "compiler/ast/expression.h" // Need Identifier and Expression base
#include "compiler/lexer/token.h"
#include <string>
#include <memory> // For std::unique_ptr
#include <utility> // For std::move
#include <sstream> // For toString implementation

// Base class for all statement nodes in the AST
class Statement : public Node {
public:
    // Pure virtual function to mark this as a Statement node type.
    virtual void statementNode() const = 0;
};

// Represents a variable declaration statement, e.g., var x; or var y = 10;
class VarStatement : public Statement {
public:
    Token token; // The 'var' token
    std::unique_ptr<Identifier> name; // The variable name (Identifier node)
    std::unique_ptr<Expression> value; // The initializer expression (can be nullptr)

    // Constructor for declaration without initializer
    VarStatement(Token t, std::unique_ptr<Identifier> n)
        : token(std::move(t)), name(std::move(n)), value(nullptr) {}

    // Constructor for declaration with initializer
    VarStatement(Token t, std::unique_ptr<Identifier> n, std::unique_ptr<Expression> v)
        : token(std::move(t)), name(std::move(n)), value(std::move(v)) {}

    std::string tokenLiteral() const override { return token.literal; } // Should be "var"

    std::string toString() const override {
        std::stringstream ss;
        ss << tokenLiteral() << " ";
        ss << (name ? name->toString() : "<null_name>");
        if (value) {
            ss << " = " << value->toString();
        }
        ss << ";"; // Typically statements end with a semicolon representation
        return ss.str();
    }

    void statementNode() const override {} // Implement dummy marker
};

#endif // STATEMENT_H
