#ifndef PROGRAM_H
#define PROGRAM_H

#include "compiler/ast/node.h"
#include "compiler/ast/statement.h" // Program contains statements
#include <vector>
#include <memory> // For unique_ptr
#include <string>
#include <sstream> // For toString

// Represents the root node of the AST
class Program : public Node {
public:
    std::vector<std::unique_ptr<Statement>> statements;

    Program() = default; // Default constructor

    // Implement Node interface
    std::string tokenLiteral() const override {
        // A program doesn't directly correspond to a single token,
        // but we can return the literal of the first statement if it exists.
        if (!statements.empty() && statements[0]) {
            return statements[0]->tokenLiteral();
        } else {
            return ""; // Empty program
        }
    }

    std::string toString() const override {
        std::stringstream ss;
        for (const auto& stmt : statements) {
            if (stmt) {
                ss << stmt->toString();
                // Optionally add a newline or separator between statements
                // ss << "\n";
            }
        }
        return ss.str();
    }
};

#endif // PROGRAM_H