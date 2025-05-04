#ifndef PARSER_H
#define PARSER_H

#include "compiler/lexer/lexer.h" // Needs Lexer
#include "compiler/ast/program.h" // Needs Program (assuming it exists or will be created)
#include "compiler/ast/statement.h"
#include "compiler/ast/expression.h"
#include "compiler/lexer/token.h" // Include Token definition
#include <vector>
#include <string>
#include <memory> // For unique_ptr

// Define precedence levels for operators (will be expanded later)
enum Precedence {
    LOWEST,
    // Add other levels like EQUALS, LESSGREATER, SUM, PRODUCT, PREFIX, CALL, INDEX
};

class Parser {
public:
    // Constructor takes a reference to a Lexer
    explicit Parser(Lexer& l);

    // Parses the entire program and returns the root AST node (Program)
    std::unique_ptr<Program> parseProgram();

    // Returns a list of errors encountered during parsing
    const std::vector<std::string>& getErrors() const;

private:
    Lexer& lexer; // Reference to the lexer providing tokens
    std::vector<std::string> errors; // List of parsing errors

    Token currentToken;
    Token peekToken;

    // Helper to advance tokens
    void nextToken();

    // Parsing methods
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<ExpressionStatement> parseExpressionStatement();
    std::unique_ptr<Expression> parseExpression(Precedence precedence);

    // Prefix parsing functions (will likely become a map later)
    std::unique_ptr<Expression> parseStringLiteral();

    // Add private helper methods for parsing different constructs later
};

#endif // PARSER_H
