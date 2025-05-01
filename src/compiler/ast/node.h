#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory> // For potential use with smart pointers later

// Forward declare Token if needed, or include token.h if Token info is stored directly
// #include "compiler/lexer/token.h"

// Base interface for all nodes in the Abstract Syntax Tree (AST)
class Node {
public:
    // Virtual destructor is crucial for classes intended for polymorphic use
    virtual ~Node() = default;

    // Returns the literal value of the token this node is associated with.
    // Useful for debugging and testing.
    virtual std::string tokenLiteral() const = 0;

    // Returns a string representation of the AST node.
    // Useful for debugging and visualizing the AST.
    virtual std::string toString() const = 0;

    // Potential future additions:
    // - virtual void accept(Visitor& visitor) = 0; // For Visitor pattern
    // - Token token; // Store the primary token associated with the node
};

// Define common types for AST nodes if needed, e.g., using smart pointers
// using NodePtr = std::unique_ptr<Node>;

#endif // NODE_H
