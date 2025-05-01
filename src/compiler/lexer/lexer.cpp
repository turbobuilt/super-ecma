// filepath: /Users/hans/prg/superecma/src/compiler/lexer/lexer.cpp
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_types.h" // Need for lookupIdentifier

// Constructor initializes the lexer with the input string
Lexer::Lexer(std::string_view input)
    : input(input), position(0), readPosition(0), ch(0), line(1), column(0) { // Initialize line=1, col=0
    readChar(); // Initialize ch, readPosition, and set initial column
}

// Reads the next character from the input and advances the position
void Lexer::readChar() {
    if (readPosition >= input.length()) {
        ch = 0; // Use 0 (NUL) to signify EOF or end of input
        // Don't advance column past end
    } else {
        ch = input[readPosition];
        if (ch == '\n') {
            line++;
            column = 0; // Reset column after newline
        } else {
            column++;
        }
    }
    position = readPosition;
    readPosition += 1;
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
        readChar(); // readChar handles line/column updates
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
    // Identifiers start with a letter or underscore
    // No need to check isLetter(ch) here, as it's checked before calling
    while (isLetter(ch) || isDigit(ch)) { // Allow letters and digits
        readChar();
    }
    // Return a view of the identifier from the original input string
    return input.substr(startPosition, position - startPosition);
}

// Reads a number (sequence of digits)
std::string_view Lexer::readNumber() {
    int startPosition = position;
    while (isDigit(ch)) {
        readChar();
    }
    // Return a view of the number from the original input string
    return input.substr(startPosition, position - startPosition);
}

// Returns the next token recognized from the input stream
Token Lexer::nextToken() {
    Token tok;

    skipWhitespace(); // Skip any preceding whitespace

    // Capture the starting position *after* skipping whitespace
    int startLine = line;
    int startCol = column;

    // Handle specific single characters first
    switch (ch) {
        case '=':
            if (peekChar() == '=') {
                readChar(); // Consume the first '='
                readChar(); // Consume the second '='
                tok = Token(TokenType::Equal, "==", startLine, startCol);
            } else {
                readChar(); // Consume the '='
                tok = Token(TokenType::Assign, "=", startLine, startCol);
            }
            break; // Added break
        case ';':
            readChar(); // Consume the ';'
            tok = Token(TokenType::Semicolon, ";", startLine, startCol);
            break;
        case ':':
            readChar(); // Consume the ':'
            tok = Token(TokenType::Colon, ":", startLine, startCol);
            break;
        case ',':
            readChar(); // Consume the ','
            tok = Token(TokenType::Comma, ",", startLine, startCol);
            break;
        case '.':
            readChar(); // Consume the '.'
            tok = Token(TokenType::Dot, ".", startLine, startCol);
            break;
        case '(':
            readChar(); // Consume the '('
            tok = Token(TokenType::LParen, "(", startLine, startCol);
            break;
        case ')':
            readChar(); // Consume the ')'
            tok = Token(TokenType::RParen, ")", startLine, startCol);
            break;
        case '{':
            readChar(); // Consume the '{'
            tok = Token(TokenType::LBrace, "{", startLine, startCol);
            break;
        case '}':
            readChar(); // Consume the '}'
            tok = Token(TokenType::RBrace, "}", startLine, startCol);
            break;
        case '[':
            readChar(); // Consume the '['
            tok = Token(TokenType::LBracket, "[", startLine, startCol);
            break;
        case ']':
            readChar(); // Consume the ']'
            tok = Token(TokenType::RBracket, "]", startLine, startCol);
            break;
        case '+':
            readChar(); // Consume the '+'
            tok = Token(TokenType::Plus, "+", startLine, startCol);
            break;
        case '-':
            readChar(); // Consume the '-'
            tok = Token(TokenType::Minus, "-", startLine, startCol);
            break;
        case '*':
            readChar(); // Consume the '*'
            tok = Token(TokenType::Asterisk, "*", startLine, startCol);
            break;
        case '/':
            readChar(); // Consume the '/'
            tok = Token(TokenType::Slash, "/", startLine, startCol);
            break;
        case '!':
            if (peekChar() == '=') {
                readChar(); // Consume the '!'
                readChar(); // Consume the '='
                tok = Token(TokenType::NotEqual, "!=", startLine, startCol);
            } else {
                readChar(); // Consume the '!'
                tok = Token(TokenType::Bang, "!", startLine, startCol);
            }
            break; // Added break
        case '<':
            if (peekChar() == '=') {
                readChar(); // Consume the '<'
                readChar(); // Consume the '='
                tok = Token(TokenType::LessThanOrEqual, "<=", startLine, startCol);
            } else {
                readChar(); // Consume the '<'
                tok = Token(TokenType::LessThan, "<", startLine, startCol);
            }
            break; // Added break
        case '>':
            if (peekChar() == '=') {
                readChar(); // Consume the '>'
                readChar(); // Consume the '='
                tok = Token(TokenType::GreaterThanOrEqual, ">=", startLine, startCol);
            } else {
                readChar(); // Consume the '>'
                tok = Token(TokenType::GreaterThan, ">", startLine, startCol);
            }
            break; // Added break
        case 0: // Handle EOF
            // For EOF, the position might be considered the end of the last line
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
                readChar(); // Consume the illegal character
                tok = Token(TokenType::Illegal, std::string(1, illegalChar), startLine, startCol);
                return tok; // Return immediately after consuming illegal char
            }
            // Removed break as default cases now return directly or fall through to EOF
    }

    // Removed redundant readChar() call here, it's handled within each case or by helper functions
    return tok;
}
