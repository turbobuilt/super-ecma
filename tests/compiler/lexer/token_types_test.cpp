// filepath: /Users/hans/prg/superecma/tests/compiler/lexer/token_types_test.cpp
#include "compiler/lexer/token_types.h" // Adjust include path relative to tests directory
#include "test_runner.h" // Include the test runner header

#include <string>
#include <vector>

// Test case for verifying the tokenTypeToString helper function
TEST_CASE(TestTokenTypeToString) {
    std::vector<std::pair<TokenType, std::string>> tests = {
        {TokenType::Var, "Var"},
        {TokenType::Identifier, "Identifier"},
        {TokenType::IntegerLiteral, "IntegerLiteral"},
        {TokenType::Assign, "Assign"},
        {TokenType::Semicolon, "Semicolon"},
        {TokenType::LParen, "LParen"},
        {TokenType::EndOfFile, "EndOfFile"},
        {TokenType::Illegal, "Illegal"}
        // Add more representative cases if needed
    };

    for (const auto& test : tests) {
        std::string result = tokenTypeToString(test.first);
        ASSERT_EQ(result, test.second);
    }
}
