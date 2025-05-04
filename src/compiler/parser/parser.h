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
#include <map> // For prefix/infix maps
#include <functional> // For std::function

// Define precedence levels for operators
enum Precedence {
    LOWEST,
    EQUALS,       // ==
    LESSGREATER,  // > or <
    SUM,          // +
    PRODUCT,      // *
    PREFIX,       // -X or !X
    CALL,         // myFunction(X)
    INDEX         // array[index]
};

// Forward declare Expression
class Expression;

// Define function types for parsing
using prefixParseFn = std::function<std::unique_ptr<Expression>()>;
using infixParseFn = std::function<std::unique_ptr<Expression>(std::unique_ptr<Expression>)>;

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

    // Pratt parser maps
    std::map<TokenType, prefixParseFn> prefixParseFns;
    std::map<TokenType, infixParseFn> infixParseFns;
    std::map<TokenType, Precedence> precedences;

    // Helper to advance tokens
    void nextToken();

    // Helper to get precedence
    Precedence peekPrecedence();
    Precedence currentPrecedence();

    // Registration functions for parse functions
    void registerPrefix(TokenType type, prefixParseFn fn);
    void registerInfix(TokenType type, infixParseFn fn);

    // Error handling
    void peekError(TokenType expected);

    // Parsing methods
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<ExpressionStatement> parseExpressionStatement();
    std::unique_ptr<Expression> parseExpression(Precedence precedence);

    // Prefix parsing functions
    std::unique_ptr<Expression> parseIdentifier();
    std::unique_ptr<Expression> parseStringLiteral();
    // Add parseIntegerLiteral, parseBoolean, parseGroupedExpression, parseIfExpression etc. later

    // Infix parsing functions
    std::unique_ptr<Expression> parseCallExpression(std::unique_ptr<Expression> function);

    // Helper for parsing call arguments
    std::vector<std::unique_ptr<Expression>> parseCallArguments();
};

#endif // PARSER_H
