// filepath: /Users/hans/prg/superecma/src/compiler/lexer/lexer.cpp
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_types.h" // Need for lookupIdentifier

// Constructor initializes the lexer with the input string
Lexer::Lexer(std::string_view input)
    : input(input), position(0), readPosition(0), ch(0) {
    readChar(); // Initialize ch and readPosition
}

// Reads the next character from the input and advances the position
void Lexer::readChar() {
    if (readPosition >= input.length()) {
        ch = 0; // Use 0 (NUL) to signify EOF or end of input
    } else {
        ch = input[readPosition];
    }
    position = readPosition;
    readPosition += 1;
}

// Helper function to skip whitespace characters
void Lexer::skipWhitespace() {
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        readChar();
    }
}

// Helper method to check if a character is a letter (a-z, A-Z, _)
// Underscore is often allowed in identifiers.
bool Lexer::isLetter(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

// Helper method to check if a character is a digit (0-9)
bool Lexer::isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

// Reads an identifier (sequence of letters/digits starting with letter/_)
std::string_view Lexer::readIdentifier() {
    int startPosition = position;
    // For this task, we only need to recognize 'var', so just reading letters is enough.
    // Future tasks will extend this to include digits after the first letter.
    while (isLetter(ch)) { // Keep reading as long as it's a letter
        readChar();
    }
    // Return a view of the identifier from the original input string
    return input.substr(startPosition, position - startPosition);
}

// Returns the next token recognized from the input stream
Token Lexer::nextToken() {
    Token tok;

    skipWhitespace(); // Skip any preceding whitespace

    int startLine = position; // Placeholder for line/col tracking
    int startCol = position;  // Placeholder for line/col tracking

    // Handle identifiers and keywords
    if (isLetter(ch)) {
        std::string_view literal = readIdentifier();
        TokenType type = lookupIdentifier(literal); // Check if it's a keyword
        // Use startLine/startCol for position for now
        tok = Token(type, std::string(literal), startLine, startCol);
        return tok; // Return early after processing identifier/keyword
    }
    // Handle EOF
    else if (ch == 0) {
        tok = Token(TokenType::EndOfFile, "", position, position);
    }
    // Handle other characters (currently illegal)
    else {
        // Placeholder for future token recognition (operators, numbers, etc.)
        tok = Token(TokenType::Illegal, std::string(1, ch), position, position);
        readChar(); // Consume the character
    }

    return tok;
}
