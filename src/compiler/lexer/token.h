// filepath: /Users/hans/prg/superecma/src/compiler/lexer/token.h
#ifndef TOKEN_H
#define TOKEN_H

#include "compiler/lexer/token_types.h" // Include the TokenType definition
#include <string>
#include <utility> // For std::move
#include <ostream> // Include for ostream operator overload

// Structure to represent a token produced by the lexer
struct Token {
    TokenType type;       // The type of the token (e.g., Identifier, IntegerLiteral)
    std::string literal;  // The actual string value of the token (e.g., "myVar", "123")
    int line;             // The line number where the token starts (1-based)
    int column;           // The column number where the token starts (1-based)

    // Constructor for easy initialization
    Token(TokenType t, std::string lit, int l, int c)
        : type(t), literal(std::move(lit)), line(l), column(c) {}

    // Default constructor (useful in some contexts, though less common for tokens)
    Token() : type(TokenType::Illegal), literal(""), line(0), column(0) {}

    // Equality operator for easy comparison in tests
    bool operator==(const Token& other) const {
        return type == other.type &&
               literal == other.literal &&
               line == other.line &&
               column == other.column;
    }

    // Inequality operator (often useful alongside ==)
    bool operator!=(const Token& other) const {
        return !(*this == other);
    }

    // Helper function for string representation (useful for debugging)
    std::string toString() const {
        // Correctly concatenate and quote the literal
        return "Token(Type: " + tokenTypeToString(type) +
               ", Literal: \"" + literal + "\"" + // Add escaped quotes around literal
               ", Line: " + std::to_string(line) +
               ", Column: " + std::to_string(column) + ")";
    }
};

// Overload the << operator for std::ostream to allow printing Token objects
inline std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.toString(); // Use the existing toString method
    return os;
}

#endif // TOKEN_H
