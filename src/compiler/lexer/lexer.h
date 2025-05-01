// filepath: /Users/hans/prg/superecma/src/compiler/lexer/lexer.h
#ifndef LEXER_H
#define LEXER_H

#include "compiler/lexer/token.h"
#include <string>
#include <string_view>
#include <unordered_map> // Include for keyword map

class Lexer {
public:
    // Constructor taking a string_view for efficiency
    explicit Lexer(std::string_view input);

    // Returns the next token in the input stream
    Token nextToken();

private:
    std::string_view input; // The input source code
    int position;           // Current position in input (points to current char)
    int readPosition;       // Current reading position in input (after current char)
    char ch;                // Current char under examination
    int line;               // Current line number (1-based)
    int column;             // Current column number (1-based, position of 'ch')

    // Helper method to read the next character and advance position
    void readChar();
    // Helper method to look at the next character without consuming
    char peekChar() const;
    // Helper method to skip whitespace characters
    void skipWhitespace();
    // Helper method to read an identifier (sequence of letters/digits/_)
    std::string_view readIdentifier();
    // Helper method to read a number (sequence of digits)
    std::string_view readNumber();
    // Helper method to check if a character is a letter (a-z, A-Z, _)
    static bool isLetter(char ch);
    // Helper method to check if a character is a digit (0-9)
    static bool isDigit(char ch); // Added for completeness, used in next tasks
};

#endif // LEXER_H
