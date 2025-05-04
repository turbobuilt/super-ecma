// filepath: /Users/hans/prg/superecma/src/compiler/lexer/token_types.h
#ifndef TOKEN_TYPES_H
#define TOKEN_TYPES_H

#include <string>
#include <string_view> // Added for keyword lookup
#include <unordered_map>
#include <ostream> // Include for ostream operator overload

enum class TokenType {
    // Special Tokens
    Illegal, // Represents a token/character we don't know about
    EndOfFile, // Represents the end of the input file

    // Identifiers & Literals
    Identifier, // foo, bar, x, y, ...
    IntegerLiteral, // 123, 0, 999
    FloatLiteral, // 3.14, 0.5, 100.0
    StringLiteral, // "hello", "world"

    // Keywords (from lang.md and plan.md)
    Var,        // var
    Wild,       // wild
    Run,        // run
    Destroy,    // destroy
    Ref,        // ref
    Capture,    // capture
    Transfer,   // transfer
    Defer,      // defer
    Using,      // using
    Function,   // function
    Return,     // return
    If,         // if
    Else,       // else
    For,        // for
    While,      // while
    True,       // true
    False,      // false
    Null,       // null
    Int,        // int (type annotation)
    Float,      // float (type annotation)
    String,     // string (type annotation)
    // Add more keywords as needed

    // Operators
    Assign,             // =
    Plus,               // +
    Minus,              // -
    Asterisk,           // *
    Slash,              // /
    Bang,               // !
    LessThan,           // <
    GreaterThan,        // >
    Equal,              // ==
    NotEqual,           // !=
    LessThanOrEqual,    // <=
    GreaterThanOrEqual, // >=
    // Add more operators as needed

    // Delimiters
    Comma,      // ,
    Semicolon,  // ;
    Colon,      // :
    LParen,     // (
    RParen,     // )
    LBrace,     // {
    RBrace,     // }
    LBracket,   // [
    RBracket,   // ]
    Dot         // .
};

// Map for keyword lookup
inline const std::unordered_map<std::string_view, TokenType>& getKeywords() {
    static const std::unordered_map<std::string_view, TokenType> keywords = {
        {"var", TokenType::Var},
        // {"wild", TokenType::Wild}, // Add keywords as they are implemented
        // {"run", TokenType::Run},
        // ... other keywords
        {"function", TokenType::Function},
        {"return", TokenType::Return},
        {"if", TokenType::If},
        {"else", TokenType::Else},
        {"for", TokenType::For},
        {"while", TokenType::While},
        {"true", TokenType::True},
        {"false", TokenType::False},
        {"null", TokenType::Null},
        // {"int", TokenType::Int}, // Type annotations might be handled differently
        // {"float", TokenType::Float},
        // {"string", TokenType::String},
    };
    return keywords;
}

// Helper function to convert TokenType to string for debugging/testing
inline std::string tokenTypeToString(TokenType type) {
    static const std::unordered_map<TokenType, std::string> typeStrings = {
        {TokenType::Illegal, "Illegal"}, {TokenType::EndOfFile, "EndOfFile"},
        {TokenType::Identifier, "Identifier"}, {TokenType::IntegerLiteral, "IntegerLiteral"},
        {TokenType::FloatLiteral, "FloatLiteral"}, {TokenType::StringLiteral, "StringLiteral"},
        {TokenType::Var, "Var"}, {TokenType::Wild, "Wild"}, {TokenType::Run, "Run"},
        {TokenType::Destroy, "Destroy"}, {TokenType::Ref, "Ref"}, {TokenType::Capture, "Capture"},
        {TokenType::Transfer, "Transfer"}, {TokenType::Defer, "Defer"}, {TokenType::Using, "Using"},
        {TokenType::Function, "Function"}, {TokenType::Return, "Return"}, {TokenType::If, "If"},
        {TokenType::Else, "Else"}, {TokenType::For, "For"}, {TokenType::While, "While"},
        {TokenType::True, "True"}, {TokenType::False, "False"}, {TokenType::Null, "Null"},
        {TokenType::Int, "Int"}, {TokenType::Float, "Float"}, {TokenType::String, "String"},
        {TokenType::Assign, "Assign"}, {TokenType::Plus, "Plus"}, {TokenType::Minus, "Minus"},
        {TokenType::Asterisk, "Asterisk"}, {TokenType::Slash, "Slash"}, {TokenType::Bang, "Bang"},
        {TokenType::LessThan, "LessThan"}, {TokenType::GreaterThan, "GreaterThan"},
        {TokenType::Equal, "Equal"}, {TokenType::NotEqual, "NotEqual"},
        {TokenType::LessThanOrEqual, "LessThanOrEqual"}, {TokenType::GreaterThanOrEqual, "GreaterThanOrEqual"},
        {TokenType::Comma, "Comma"}, {TokenType::Semicolon, "Semicolon"}, {TokenType::Colon, "Colon"},
        {TokenType::LParen, "LParen"}, {TokenType::RParen, "RParen"}, {TokenType::LBrace, "LBrace"},
        {TokenType::RBrace, "RBrace"}, {TokenType::LBracket, "LBracket"}, {TokenType::RBracket, "RBracket"},
        {TokenType::Dot, "Dot"}
    };

    auto it = typeStrings.find(type);
    if (it != typeStrings.end()) {
        return it->second;
    }
    return "UnknownTokenType"; // Should not happen
}

// Helper function to lookup identifier and return keyword type or Identifier
inline TokenType lookupIdentifier(std::string_view identifier) {
    const auto& keywords = getKeywords();
    auto it = keywords.find(identifier);
    if (it != keywords.end()) {
        return it->second; // Found a keyword
    }
    return TokenType::Identifier; // Not a keyword, must be an identifier
}

// Overload the << operator for std::ostream to allow printing TokenType enums
inline std::ostream& operator<<(std::ostream& os, const TokenType& type) {
    os << tokenTypeToString(type);
    return os;
}

#endif // TOKEN_TYPES_H
