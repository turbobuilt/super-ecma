#include "compiler/ast/expression.h"
#include "compiler/lexer/token.h" // Need Token definition
#include "test_runner.h"
#include <string>
#include <limits> // For numeric limits if needed

// Test case for IntegerLiteral node
TEST_CASE(TestIntegerLiteralNode) {
    Token intToken(TokenType::IntegerLiteral, "12345", 1, 10);
    int64_t expectedValue = 12345;
    IntegerLiteral intLit(intToken, expectedValue);

    ASSERT_EQ(intLit.tokenLiteral(), "12345");
    ASSERT_EQ(intLit.toString(), "12345");
    ASSERT_EQ(intLit.value, expectedValue);
    ASSERT_EQ(intLit.token.type, TokenType::IntegerLiteral);
    ASSERT_EQ(intLit.token.line, 1);
    ASSERT_EQ(intLit.token.column, 10);

    // Test polymorphism (optional but good practice)
    Expression* exprPtr = &intLit;
    ASSERT_EQ(exprPtr->tokenLiteral(), "12345");
    ASSERT_EQ(exprPtr->toString(), "12345");
}

// Test case for FloatLiteral node
TEST_CASE(TestFloatLiteralNode) {
    Token floatToken(TokenType::FloatLiteral, "3.14159", 2, 5);
    double expectedValue = 3.14159;
    FloatLiteral floatLit(floatToken, expectedValue);

    ASSERT_EQ(floatLit.tokenLiteral(), "3.14159");
    ASSERT_EQ(floatLit.toString(), "3.14159");
    // Use a tolerance for floating-point comparisons if necessary,
    // but direct comparison should work for this simple case.
    ASSERT_EQ(floatLit.value, expectedValue);
    ASSERT_EQ(floatLit.token.type, TokenType::FloatLiteral);
    ASSERT_EQ(floatLit.token.line, 2);
    ASSERT_EQ(floatLit.token.column, 5);

    // Test polymorphism
    Expression* exprPtr = &floatLit;
    ASSERT_EQ(exprPtr->tokenLiteral(), "3.14159");
    ASSERT_EQ(exprPtr->toString(), "3.14159");
}

// Test case for StringLiteral node
TEST_CASE(TestStringLiteralNode) {
    // Note: Token literal includes quotes, node value typically doesn't
    Token stringToken(TokenType::StringLiteral, "\"hello world\"", 3, 1);
    std::string expectedValue = "hello world"; // Value without quotes
    StringLiteral stringLit(stringToken, expectedValue);

    ASSERT_EQ(stringLit.tokenLiteral(), "\"hello world\"");
    ASSERT_EQ(stringLit.toString(), "\"hello world\""); // toString matches token literal
    ASSERT_EQ(stringLit.value, expectedValue);
    ASSERT_EQ(stringLit.token.type, TokenType::StringLiteral);
    ASSERT_EQ(stringLit.token.line, 3);
    ASSERT_EQ(stringLit.token.column, 1);

    // Test polymorphism
    Expression* exprPtr = &stringLit;
    ASSERT_EQ(exprPtr->tokenLiteral(), "\"hello world\"");
    ASSERT_EQ(exprPtr->toString(), "\"hello world\"");
}

// Test case for Identifier node
TEST_CASE(TestIdentifierNode) {
    Token identToken(TokenType::Identifier, "myVariable", 4, 15);
    std::string expectedValue = "myVariable";
    Identifier ident(identToken, expectedValue);

    ASSERT_EQ(ident.tokenLiteral(), "myVariable");
    ASSERT_EQ(ident.toString(), "myVariable"); // toString returns the value/name
    ASSERT_EQ(ident.value, expectedValue);
    ASSERT_EQ(ident.token.type, TokenType::Identifier);
    ASSERT_EQ(ident.token.line, 4);
    ASSERT_EQ(ident.token.column, 15);

    // Test polymorphism
    Expression* exprPtr = &ident;
    ASSERT_EQ(exprPtr->tokenLiteral(), "myVariable");
    ASSERT_EQ(exprPtr->toString(), "myVariable");
}
