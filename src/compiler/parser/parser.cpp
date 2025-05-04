#include "compiler/parser/parser.h"
#include "compiler/lexer/token.h" // Include necessary headers
#include "compiler/ast/expression.h" // Include Expression AST nodes
#include "compiler/ast/statement.h" // Include Statement AST nodes
#include <iostream> // For placeholder output/errors
#include <string> // For std::string
#include <map> // For precedences map

// Map token types to precedence levels
std::map<TokenType, Precedence> precedences = {
    {TokenType::Equals, Precedence::EQUALS},
    {TokenType::NotEquals, Precedence::EQUALS},
    {TokenType::LessThan, Precedence::LESSGREATER},
    {TokenType::GreaterThan, Precedence::LESSGREATER},
    {TokenType::Plus, Precedence::SUM},
    {TokenType::Minus, Precedence::SUM},
    {TokenType::Slash, Precedence::PRODUCT},
    {TokenType::Asterisk, Precedence::PRODUCT},
    {TokenType::LParen, Precedence::CALL} // For function calls
    // Add other operators like LBRACKET for index
};

// Constructor implementation
Parser::Parser(Lexer& l) : lexer(l) {
    // Read two tokens, so currentToken and peekToken are both set
    nextToken();
    nextToken();

    // Register prefix parsing functions
    registerPrefix(TokenType::Identifier, [this] { return parseIdentifier(); });
    registerPrefix(TokenType::StringLiteral, [this] { return parseStringLiteral(); });
    // Register IntegerLiteral, Boolean, LParen (grouped), If, Function etc. later

    // Register infix parsing functions
    registerInfix(TokenType::LParen, [this](std::unique_ptr<Expression> left) {
        return parseCallExpression(std::move(left));
    });
    // Register +, -, *, /, ==, !=, <, > etc. later
}

// Helper to advance tokens
void Parser::nextToken() {
    currentToken = peekToken;
    peekToken = lexer.nextToken();
}

// Helper to get precedence of the *next* token
Precedence Parser::peekPrecedence() {
    if (precedences.count(peekToken.type)) {
        return precedences[peekToken.type];
    }
    return Precedence::LOWEST;
}

// Helper to get precedence of the *current* token
Precedence Parser::currentPrecedence() {
    if (precedences.count(currentToken.type)) {
        return precedences[currentToken.type];
    }
    return Precedence::LOWEST;
}

// Register a prefix parsing function
void Parser::registerPrefix(TokenType type, prefixParseFn fn) {
    prefixParseFns[type] = fn;
}

// Register an infix parsing function
void Parser::registerInfix(TokenType type, infixParseFn fn) {
    infixParseFns[type] = fn;
}

// Error handling for unexpected peek token
void Parser::peekError(TokenType expected) {
    std::string msg = "Expected next token to be " + tokenTypeToString(expected) +
                      ", got " + tokenTypeToString(peekToken.type) + " instead";
    errors.push_back(msg);
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

// Parses an expression using Pratt parsing
std::unique_ptr<Expression> Parser::parseExpression(Precedence precedence) {
    // Check if a prefix function exists for the current token type
    if (prefixParseFns.find(currentToken.type) == prefixParseFns.end()) {
        std::string errorMsg = "No prefix parse function for " + tokenTypeToString(currentToken.type) + " found";
        errors.push_back(errorMsg);
        return nullptr;
    }
    prefixParseFn prefix = prefixParseFns[currentToken.type];
    std::unique_ptr<Expression> leftExp = prefix();

    // While the next token is not a semicolon and the next token's precedence
    // is higher than the current binding precedence, parse infix expressions.
    while (peekToken.type != TokenType::Semicolon && precedence < peekPrecedence()) {
        // Check if an infix function exists for the *next* token
        if (infixParseFns.find(peekToken.type) == infixParseFns.end()) {
            return leftExp; // No infix operator found, return the left expression
        }
        infixParseFn infix = infixParseFns[peekToken.type];

        nextToken(); // Consume the operator token

        leftExp = infix(std::move(leftExp)); // Call the infix function
    }

    return leftExp;
}

// Prefix parsing function for identifiers
std::unique_ptr<Expression> Parser::parseIdentifier() {
    return std::make_unique<Identifier>(currentToken, currentToken.literal);
}

// Prefix parsing function for string literals
std::unique_ptr<Expression> Parser::parseStringLiteral() {
    // The currentToken is the StringLiteral token
    // The literal value in the token includes the quotes, but the AST node
    // should store the content *without* quotes. The lexer already handles this.
    return std::make_unique<StringLiteral>(currentToken, currentToken.literal);
}

// Infix parsing function for function calls
std::unique_ptr<Expression> Parser::parseCallExpression(std::unique_ptr<Expression> function) {
    // currentToken is '('
    auto exp = std::make_unique<CallExpression>(currentToken, std::move(function));
    exp->arguments = parseCallArguments();
    return exp;
}

// Helper function to parse the arguments of a function call
std::vector<std::unique_ptr<Expression>> Parser::parseCallArguments() {
    std::vector<std::unique_ptr<Expression>> args;

    // Check if there are no arguments (e.g., myFunction())
    if (peekToken.type == TokenType::RParen) {
        nextToken(); // Consume ')'
        return args;
    }

    // Parse the first argument
    nextToken(); // Consume '(' or ','
    args.push_back(parseExpression(Precedence::LOWEST));

    // Parse subsequent arguments separated by commas
    while (peekToken.type == TokenType::Comma) {
        nextToken(); // Consume ','
        nextToken(); // Move to the start of the next expression
        args.push_back(parseExpression(Precedence::LOWEST));
    }

    // Expect a closing parenthesis
    if (peekToken.type != TokenType::RParen) {
        peekError(TokenType::RParen);
        return {}; // Return empty vector on error
    }
    nextToken(); // Consume ')'

    return args;
}

// Implementation for getErrors
const std::vector<std::string>& Parser::getErrors() const {
    return errors;
}
