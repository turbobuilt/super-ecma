// filepath: /Users/hans/prg/superecma/src/compiler/lexer/lexer.cpp
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_types.h" // Need for lookupIdentifier

// Constructor initializes the lexer with the input string
Lexer::Lexer(std::string_view input)
    : input(input), position(0), readPosition(0), ch(0), line(1), column(0) { // Initialize line=1, col=0
    readChar(); // Read the first character, setting initial line/column
}

// Reads the next character from the input and advances the position
void Lexer::readChar() {
    // Update column based on the character *just processed* (the one currently in ch)
    if (ch == '\n') {
        line++;
        column = 0; // Reset column for the new line
    }
    // Increment column *before* reading the next char
    column++;

    if (readPosition >= input.length()) {
        ch = 0; // Use 0 (NUL) to signify EOF or end of input
        // Column is already incremented past the last character
    } else {
        ch = input[readPosition]; // Read the next character
    }
    position = readPosition; // Update position to the start of the char just read
    readPosition += 1;       // Advance read position for the *next* call
}

// Helper method to look at the next character without consuming
char Lexer::peekChar() const {
    if (readPosition >= input.length()) {
        return 0; // EOF
    } else {
        return input[readPosition];
    }
}

// Helper function to skip whitespace characters
void Lexer::skipWhitespace() {
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        readChar(); // readChar handles line/column updates correctly now
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
    // Loop while the *current* character is valid for an identifier
    while (isLetter(ch) || isDigit(ch)) {
        readChar(); // Consume the valid character and read the next one
    }
    // Return a view of the identifier from the original input string
    return input.substr(startPosition, position - startPosition);
}

// Reads a number (sequence of digits)
std::string_view Lexer::readNumber() {
    int startPosition = position;
    // Loop while the *current* character is a digit
    while (isDigit(ch)) {
        readChar(); // Consume the digit and read the next one
    }
    // Return a view of the number from the original input string
    return input.substr(startPosition, position - startPosition);
}

// Returns the next token recognized from the input stream
Token Lexer::nextToken() {
    Token tok;

    skipWhitespace(); // Skip any preceding whitespace

    // Capture the starting position *after* skipping whitespace
    // 'line' and 'column' now correctly point to the start of 'ch'
    int startLine = line;
    int startCol = column;

    // Handle specific single characters first
    switch (ch) {
        case '=':
            if (peekChar() == '=') {
                readChar(); // Consume the first '='
                readChar(); // Consume the second '=', advances position/line/col
                tok = Token(TokenType::Equal, "==", startLine, startCol);
            } else {
                readChar(); // Consume the '=', advances position/line/col
                tok = Token(TokenType::Assign, "=", startLine, startCol);
            }
            return tok;
        case ';':
            readChar(); // Consume the ';', advances position/line/col
            tok = Token(TokenType::Semicolon, ";", startLine, startCol);
            return tok;
        case ':':
            readChar(); // Consume the ':', advances position/line/col
            tok = Token(TokenType::Colon, ":", startLine, startCol);
            return tok;
        case ',':
            readChar(); // Consume the ',', advances position/line/col
            tok = Token(TokenType::Comma, ",", startLine, startCol);
            return tok;
        case '.':
            readChar(); // Consume the '.', advances position/line/col
            tok = Token(TokenType::Dot, ".", startLine, startCol);
            return tok;
        case '(':
            readChar(); // Consume the '(', advances position/line/col
            tok = Token(TokenType::LParen, "(", startLine, startCol);
            return tok;
        case ')':
            readChar(); // Consume the ')', advances position/line/col
            tok = Token(TokenType::RParen, ")", startLine, startCol);
            return tok;
        case '{':
            readChar(); // Consume the '{', advances position/line/col
            tok = Token(TokenType::LBrace, "{", startLine, startCol);
            return tok;
        case '}':
            readChar(); // Consume the '}', advances position/line/col
            tok = Token(TokenType::RBrace, "}", startLine, startCol);
            return tok;
        case '[':
            readChar(); // Consume the '[', advances position/line/col
            tok = Token(TokenType::LBracket, "[", startLine, startCol);
            return tok;
        case ']':
            readChar(); // Consume the ']', advances position/line/col
            tok = Token(TokenType::RBracket, "]", startLine, startCol);
            return tok;
        case '+':
            readChar(); // Consume the '+', advances position/line/col
            tok = Token(TokenType::Plus, "+", startLine, startCol);
            return tok;
        case '-':
            readChar(); // Consume the '-', advances position/line/col
            tok = Token(TokenType::Minus, "-", startLine, startCol);
            return tok;
        case '*':
            readChar(); // Consume the '*', advances position/line/col
            tok = Token(TokenType::Asterisk, "*", startLine, startCol);
            return tok;
        case '/':
            readChar(); // Consume the '/', advances position/line/col
            tok = Token(TokenType::Slash, "/", startLine, startCol);
            return tok;
        case '!':
            if (peekChar() == '=') {
                readChar(); // Consume the '!'
                readChar(); // Consume the '=', advances position/line/col
                tok = Token(TokenType::NotEqual, "!=", startLine, startCol);
            } else {
                readChar(); // Consume the '!', advances position/line/col
                tok = Token(TokenType::Bang, "!", startLine, startCol);
            }
            return tok;
        case '<':
            if (peekChar() == '=') {
                readChar(); // Consume the '<'
                readChar(); // Consume the '=', advances position/line/col
                tok = Token(TokenType::LessThanOrEqual, "<=", startLine, startCol);
            } else {
                readChar(); // Consume the '<', advances position/line/col
                tok = Token(TokenType::LessThan, "<", startLine, startCol);
            }
            return tok;
        case '>':
            if (peekChar() == '=') {
                readChar(); // Consume the '>'
                readChar(); // Consume the '=', advances position/line/col
                tok = Token(TokenType::GreaterThanOrEqual, ">=", startLine, startCol);
            } else {
                readChar(); // Consume the '>', advances position/line/col
                tok = Token(TokenType::GreaterThan, ">", startLine, startCol);
            }
            return tok;
        case 0: // Handle EOF
            // 'line' and 'column' should be at the position *after* the last char
            tok = Token(TokenType::EndOfFile, "", line, column);
            // Don't call readChar() for EOF
            return tok;
        default:
            // Handle identifiers and keywords
            if (isLetter(ch)) {
                // startLine, startCol already captured
                std::string_view literal = readIdentifier(); // readIdentifier advances position/line/col
                TokenType type = lookupIdentifier(literal);
                tok = Token(type, std::string(literal), startLine, startCol);
                // readIdentifier already advanced position, so return directly
                return tok;
            }
            // Handle numbers (integers for now)
            else if (isDigit(ch)) {
                // startLine, startCol already captured
                std::string_view literal = readNumber(); // readNumber advances position/line/col
                tok = Token(TokenType::IntegerLiteral, std::string(literal), startLine, startCol);
                // readNumber already advanced position, so return directly
                return tok;
            }
            // Handle unknown characters
            else {
                char illegalChar = ch; // Store the illegal char before consuming
                readChar(); // Consume the illegal character, advances position/line/col
                tok = Token(TokenType::Illegal, std::string(1, illegalChar), startLine, startCol);
                return tok; // Return immediately after consuming illegal char
            }
    }
}
