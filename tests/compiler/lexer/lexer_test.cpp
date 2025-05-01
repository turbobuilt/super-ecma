// filepath: /Users/hans/prg/superecma/tests/compiler/lexer/lexer_test.cpp
#include "compiler/lexer/lexer.h"
#include "test_runner.h"

#include <vector>

// Test case for verifying EndOfFile token generation
TEST_CASE(TestLexerEOF) {
    // Test with empty input
    {
        Lexer lexer("");
        Token token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::EndOfFile);
        ASSERT_EQ(token.literal, "");
        // Line/Column might be 0 or 1 depending on convention, check consistency
        // For now, based on implementation, it might be 0,0
        ASSERT_EQ(token.line, 0); // Assuming 0-based for now from impl
        ASSERT_EQ(token.column, 0);

        // Calling nextToken again should still return EOF
        token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::EndOfFile);
    }

    // Test with non-empty input that eventually reaches EOF
    {
        Lexer lexer("abc");
        lexer.nextToken(); // Consume 'a' (returns Illegal for now)
        lexer.nextToken(); // Consume 'b' (returns Illegal for now)
        lexer.nextToken(); // Consume 'c' (returns Illegal for now)
        Token token = lexer.nextToken(); // Should be EOF
        ASSERT_EQ(token.type, TokenType::EndOfFile);
        ASSERT_EQ(token.literal, "");
        // Position will be 3 after reading 'c'
        ASSERT_EQ(token.line, 3); // Assuming 0-based for now
        ASSERT_EQ(token.column, 3);
    }
}

// Test case for skipping whitespace
TEST_CASE(TestLexerWhitespaceSkipping) {
    // Test with only whitespace
    {
        Lexer lexer("  \t \n \r\n  ");
        Token token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::EndOfFile);
    }

    // Test with tokens separated by whitespace
    // (Currently returns Illegal tokens, but checks skipping)
    {
        Lexer lexer(" a  b\tc\n d ");
        Token t1 = lexer.nextToken(); // 'a'
        Token t2 = lexer.nextToken(); // 'b'
        Token t3 = lexer.nextToken(); // 'c'
        Token t4 = lexer.nextToken(); // 'd'
        Token t5 = lexer.nextToken(); // EOF

        ASSERT_EQ(t1.type, TokenType::Illegal); // Expect Illegal for 'a' for now
        ASSERT_EQ(t1.literal, "a");
        ASSERT_EQ(t2.type, TokenType::Illegal); // Expect Illegal for 'b' for now
        ASSERT_EQ(t2.literal, "b");
        ASSERT_EQ(t3.type, TokenType::Illegal); // Expect Illegal for 'c' for now
        ASSERT_EQ(t3.literal, "c");
        ASSERT_EQ(t4.type, TokenType::Illegal); // Expect Illegal for 'd' for now
        ASSERT_EQ(t4.literal, "d");
        ASSERT_EQ(t5.type, TokenType::EndOfFile);
    }
}

// Test case for recognizing the 'var' keyword
TEST_CASE(TestLexerVarKeyword) {
    // Test basic "var"
    {
        Lexer lexer("var");
        Token token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::Var);
        ASSERT_EQ(token.literal, "var");
        // Position check (using current simple logic)
        ASSERT_EQ(token.line, 0); // Start position
        ASSERT_EQ(token.column, 0);

        token = lexer.nextToken(); // Check EOF follows
        ASSERT_EQ(token.type, TokenType::EndOfFile);
    }

    // Test "var" surrounded by whitespace
    {
        Lexer lexer("  var\t");
        Token token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::Var);
        ASSERT_EQ(token.literal, "var");
        // Position check (using current simple logic)
        ASSERT_EQ(token.line, 2); // Start position after whitespace
        ASSERT_EQ(token.column, 2);

        token = lexer.nextToken(); // Check EOF follows
        ASSERT_EQ(token.type, TokenType::EndOfFile);
    }

    // Test partial match (should be Identifier, handled in next task)
    // For now, lookupIdentifier returns Identifier if not found in map
    {
        Lexer lexer("v");
        Token token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::Identifier);
        ASSERT_EQ(token.literal, "v");
        token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::EndOfFile);
    }

    // Test longer word starting with var (should be Identifier)
    {
        Lexer lexer("variable");
        Token token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::Identifier);
        ASSERT_EQ(token.literal, "variable");
        token = lexer.nextToken();
        ASSERT_EQ(token.type, TokenType::EndOfFile);
    }

     // Test var followed by other chars (semicolon needs Task 9)
    {
        Lexer lexer("var;");
        Token t1 = lexer.nextToken(); // var
        Token t2 = lexer.nextToken(); // ; (Illegal for now)
        Token t3 = lexer.nextToken(); // EOF

        ASSERT_EQ(t1.type, TokenType::Var);
        ASSERT_EQ(t1.literal, "var");
        ASSERT_EQ(t2.type, TokenType::Illegal); // Expect Illegal until ';' is handled
        ASSERT_EQ(t2.literal, ";");
        ASSERT_EQ(t3.type, TokenType::EndOfFile);
    }
}

// Add more test cases for other tokens later...
// TEST_CASE(TestLexerBasicTokens) { ... }
