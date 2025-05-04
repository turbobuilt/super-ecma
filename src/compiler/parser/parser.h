#ifndef PARSER_H
#define PARSER_H
`
#include "compiler/lexer/lexer.h" // Needs Lexer
#include "compiler/ast/program.h" // Needs Program (assuming it exists or will be created)
#include <vector>
#include <string>
#include <memory> // For unique_ptr

// Forward declare AST nodes if needed, or include headers
// #include "compiler/ast/statement.h"
// #include "compiler/ast/expression.h"

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

    // Add private helper methods for parsing different constructs later
    // e.g., parseStatement(), parseExpression(), etc.
};

#endif // PARSER_H
