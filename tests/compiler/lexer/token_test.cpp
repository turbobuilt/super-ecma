// filepath: /Users/hans/prg/superecma/tests/compiler/lexer/token_test.cpp
#include "compiler/lexer/token.h" // Include the header for the Token struct
#include "test_runner.h" // Include the test runner utilities

#include <string>

// Test case for verifying the Token struct initialization and members
TEST_CASE(TestTokenStruct) {
    // Create some sample tokens
    Token token1(TokenType::Var, "var", 1, 1);
    Token token2(TokenType::Identifier, "myVariable", 2, 5);
    Token token3(TokenType::IntegerLiteral, "42", 3, 10);
    Token token4(TokenType::Semicolon, ";", 3, 12);

    // Assert that the members are initialized correctly
    ASSERT_EQ(token1.type, TokenType::Var);
    ASSERT_EQ(token1.literal, "var");
    ASSERT_EQ(token1.line, 1);
    ASSERT_EQ(token1.column, 1);

    ASSERT_EQ(token2.type, TokenType::Identifier);
    ASSERT_EQ(token2.literal, "myVariable");
    ASSERT_EQ(token2.line, 2);
    ASSERT_EQ(token2.column, 5);

    ASSERT_EQ(token3.type, TokenType::IntegerLiteral);
    ASSERT_EQ(token3.literal, "42");
    ASSERT_EQ(token3.line, 3);
    ASSERT_EQ(token3.column, 10);

    ASSERT_EQ(token4.type, TokenType::Semicolon);
    ASSERT_EQ(token4.literal, ";");
    ASSERT_EQ(token4.line, 3);
    ASSERT_EQ(token4.column, 12);
}

// Test case for verifying the Token equality operator
TEST_CASE(TestTokenEquality) {
    Token t1a(TokenType::Identifier, "count", 5, 2);
    Token t1b(TokenType::Identifier, "count", 5, 2); // Same as t1a
    Token t2(TokenType::Identifier, "value", 5, 2);  // Different literal
    Token t3(TokenType::Assign, "=", 5, 8);          // Different type
    Token t4(TokenType::Identifier, "count", 6, 2);  // Different line
    Token t5(TokenType::Identifier, "count", 5, 3);  // Different column

    ASSERT_TRUE(t1a == t1b); // Should be equal
    ASSERT_FALSE(t1a != t1b); // Should not be unequal

    ASSERT_FALSE(t1a == t2); // Different literal
    ASSERT_TRUE(t1a != t2);

    ASSERT_FALSE(t1a == t3); // Different type
    ASSERT_TRUE(t1a != t3);

    ASSERT_FALSE(t1a == t4); // Different line
    ASSERT_TRUE(t1a != t4);

    ASSERT_FALSE(t1a == t5); // Different column
    ASSERT_TRUE(t1a != t5);

    // Test against default constructed token
    Token defaultToken;
    ASSERT_FALSE(t1a == defaultToken);
    ASSERT_TRUE(t1a != defaultToken);
}

// Test case for the Token's toString() method (optional but helpful)
TEST_CASE(TestTokenToString) {
    Token token(TokenType::LParen, "(", 10, 20);
    // Escape the inner double quotes
    std::string expected = "Token(Type: LParen, Literal: \"(\", Line: 10, Column: 20)";
    ASSERT_EQ(token.toString(), expected);

    Token tokenIllegal; // Default constructor uses Illegal type
    // Escape the inner double quotes
    std::string expectedIllegal = "Token(Type: Illegal, Literal: \"\", Line: 0, Column: 0)";
    ASSERT_EQ(tokenIllegal.toString(), expectedIllegal);
}
