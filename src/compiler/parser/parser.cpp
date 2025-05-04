#include "compiler/parser/parser.h"
#include "compiler/lexer/token.h" // Include necessary headers
#include "compiler/ast/expression.h" // Include Expression AST nodes
#include "compiler/ast/statement.h" // Include Statement AST nodes
#include <iostream> // For placeholder output/errors
#include <string> // For std::string

// Constructor implementation
Parser::Parser(Lexer& l) : lexer(l) {
    // Read two tokens, so currentToken and peekToken are both set
    nextToken();
    nextToken();
}

// Helper to advance tokens
void Parser::nextToken() {
    currentToken = peekToken;
    peekToken = lexer.nextToken();
}

// Main parsing function
std::unique_ptr<Program> Parser::parseProgram() {
    auto program = std::make_unique<Program>();

    while (currentToken.type != TokenType::EndOfFile) {
        auto stmt = parseStatement();
        if (stmt) {
            program->statements.push_back(std::move(stmt));
        }
        nextToken(); // Move to the next token
    }

    return program;
}

// Parses a single statement
std::unique_ptr<Statement> Parser::parseStatement() {
    // For now, only expression statements are handled
    // Later, switch based on currentToken.type (e.g., Var, Return)
    return parseExpressionStatement();
}

// Parses an expression statement
std::unique_ptr<ExpressionStatement> Parser::parseExpressionStatement() {
    auto stmt = std::make_unique<ExpressionStatement>(currentToken); // Token is the first token of the expression

    stmt->expression = parseExpression(Precedence::LOWEST);

    // Optional semicolon for expression statements (common in C-like languages)
    if (peekToken.type == TokenType::Semicolon) {
        nextToken();
    }

    return stmt;
}

// Parses an expression using Pratt parsing (placeholder)
std::unique_ptr<Expression> Parser::parseExpression(Precedence precedence) {
    // Check for a prefix parse function based on the current token type
    // This will become a map lookup later
    std::unique_ptr<Expression> leftExp;
    if (currentToken.type == TokenType::StringLiteral) {
        leftExp = parseStringLiteral();
    }
    // else if (currentToken.type == TokenType::Identifier) { ... }
    // else if (currentToken.type == TokenType::IntegerLiteral) { ... }
    else {
        // Handle error: No prefix parse function found
        std::string errorMsg = "No prefix parse function for " + tokenTypeToString(currentToken.type) + " found";
        errors.push_back(errorMsg);
        return nullptr;
    }

    // Placeholder for infix parsing (not needed for single literals yet)
    // while (peekToken.type != TokenType::Semicolon && precedence < peekPrecedence()) {
    //     nextToken();
    //     leftExp = parseInfixExpression(std::move(leftExp));
    // }

    return leftExp;
}

// Prefix parsing function for string literals
std::unique_ptr<Expression> Parser::parseStringLiteral() {
    // The currentToken is the StringLiteral token
    // The literal value in the token includes the quotes, but the AST node
    // should store the content *without* quotes. The lexer already handles this.
    return std::make_unique<StringLiteral>(currentToken, currentToken.literal);
}

// Implementation for getErrors
const std::vector<std::string>& Parser::getErrors() const {
    return errors;
}
