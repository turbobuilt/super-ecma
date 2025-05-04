// filepath: /Users/hans/prg/superecma/tests/compiler/lexer/lexer_test.cpp
#include "compiler/lexer/lexer.h"
#include "test_runner.h"

#include <vector>

// Helper function for comparing token vectors
void assertTokensEqual(const std::vector<Token>& actual, const std::vector<Token>& expected) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        // Use the Token's operator== for comparison
        ASSERT_EQ(actual[i], expected[i]);
        // Optionally print details on failure for easier debugging
        if (actual[i] != expected[i]) {
             std::cerr << "Mismatch at index " << i << ":\n"
                       << "  Expected: " << expected[i].toString() << "\n"
                       << "  Actual:   " << actual[i].toString() << std::endl;
        }
    }
}

// Test case for verifying EndOfFile token generation
TEST_CASE(TestLexerEOF) {
    // Test with empty input
    {
        Lexer lexer("");
        Token token = lexer.nextToken();
        // EOF on empty input should be at line 1, col 1 (start position)
        ASSERT_EQ(token, Token(TokenType::EndOfFile, "", 1, 1));

        // Calling nextToken again should still return EOF at the same position
        token = lexer.nextToken();
        ASSERT_EQ(token, Token(TokenType::EndOfFile, "", 1, 1));
    }

    // Test with non-empty input that eventually reaches EOF
    {
        // Input: "a\nb"
        // Expected: Identifier("a", 1, 1), Identifier("b", 2, 1), EOF("", 2, 2)
        Lexer lexer("a\nb");
        Token t1 = lexer.nextToken(); // 'a'
        Token t2 = lexer.nextToken(); // 'b'
        Token t3 = lexer.nextToken(); // EOF
        ASSERT_EQ(t1, Token(TokenType::Identifier, "a", 1, 1)); // Expect Identifier
        ASSERT_EQ(t2, Token(TokenType::Identifier, "b", 2, 1)); // Expect Identifier
        ASSERT_EQ(t3, Token(TokenType::EndOfFile, "", 2, 2)); // EOF is after 'b' on line 2
    }
}

// Test case for skipping whitespace
TEST_CASE(TestLexerWhitespaceSkipping) {
    // Test with only whitespace
    {
        // Input: "  \t \n \r\n  "
        // Expected: EOF at line 3, col 3 (after the final spaces)
        Lexer lexer("  \t \n \r\n  ");
        Token token = lexer.nextToken();
        ASSERT_EQ(token, Token(TokenType::EndOfFile, "", 3, 3));
    }

    // Test with tokens separated by whitespace
    {
        // Input: " var\n age = 10 ; "
        // Expected tokens with correct line/col:
        // Var("var", 1, 2)
        // Identifier("age", 2, 2)
        // Assign("=", 2, 6)
        // IntegerLiteral("10", 2, 8)
        // Semicolon(";", 2, 11)
        // EOF("", 2, 13)
        Lexer lexer(" var\n age = 10 ; ");
        std::vector<Token> expected = {
            Token(TokenType::Var, "var", 1, 2),
            Token(TokenType::Identifier, "age", 2, 2),
            Token(TokenType::Assign, "=", 2, 6),
            Token(TokenType::IntegerLiteral, "10", 2, 8),
            Token(TokenType::Semicolon, ";", 2, 11),
            Token(TokenType::EndOfFile, "", 2, 13)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);

        assertTokensEqual(actual, expected);
    }
}

// Test case for recognizing the 'var' keyword
TEST_CASE(TestLexerVarKeyword) {
    // Test basic "var"
    {
        Lexer lexer("var");
        std::vector<Token> expected = {
            Token(TokenType::Var, "var", 1, 1),
            Token(TokenType::EndOfFile, "", 1, 4)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test "var" surrounded by whitespace
    {
        Lexer lexer("  var\t");
         std::vector<Token> expected = {
            Token(TokenType::Var, "var", 1, 3),
            Token(TokenType::EndOfFile, "", 1, 7) // EOF after tab
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test partial match (should be Identifier)
    {
        Lexer lexer("v");
         std::vector<Token> expected = {
            Token(TokenType::Identifier, "v", 1, 1),
            Token(TokenType::EndOfFile, "", 1, 2)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test longer word starting with var (should be Identifier)
    {
        Lexer lexer("variable");
         std::vector<Token> expected = {
            Token(TokenType::Identifier, "variable", 1, 1),
            Token(TokenType::EndOfFile, "", 1, 9)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

     // Test var followed by other chars
    {
        Lexer lexer("var;");
         std::vector<Token> expected = {
            Token(TokenType::Var, "var", 1, 1),
            Token(TokenType::Semicolon, ";", 1, 4),
            Token(TokenType::EndOfFile, "", 1, 5)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }
}

// Test case for recognizing identifiers
TEST_CASE(TestLexerIdentifierRecognition) {
    // Test simple identifiers
    {
        // Input: "myVar another_var\n_leadingUnderscore var123"
        Lexer lexer("myVar another_var\n_leadingUnderscore var123");
        std::vector<Token> expected = {
            Token(TokenType::Identifier, "myVar", 1, 1),
            Token(TokenType::Identifier, "another_var", 1, 7),
            Token(TokenType::Identifier, "_leadingUnderscore", 2, 1),
            Token(TokenType::Identifier, "var123", 2, 20),
            Token(TokenType::EndOfFile, "", 2, 26) // Position after last token
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test identifier followed immediately by EOF
    {
        Lexer lexer("finalIdentifier");
        std::vector<Token> expected = {
            Token(TokenType::Identifier, "finalIdentifier", 1, 1),
            Token(TokenType::EndOfFile, "", 1, 16)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test identifier mixed with keywords
    {
        Lexer lexer("var myVar var");
         std::vector<Token> expected = {
            Token(TokenType::Var, "var", 1, 1),
            Token(TokenType::Identifier, "myVar", 1, 5),
            Token(TokenType::Var, "var", 1, 11),
            Token(TokenType::EndOfFile, "", 1, 14)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }
}

// Test case for recognizing integer literals
TEST_CASE(TestLexerIntegerLiteral) {
    // Test simple integers
    {
        Lexer lexer("5 123\n0 9999");
        std::vector<Token> expected = {
            Token(TokenType::IntegerLiteral, "5", 1, 1),
            Token(TokenType::IntegerLiteral, "123", 1, 3),
            Token(TokenType::IntegerLiteral, "0", 2, 1),
            Token(TokenType::IntegerLiteral, "9999", 2, 3),
            Token(TokenType::EndOfFile, "", 2, 7)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test integer followed immediately by EOF
    {
        Lexer lexer("42");
        std::vector<Token> expected = {
            Token(TokenType::IntegerLiteral, "42", 1, 1),
            Token(TokenType::EndOfFile, "", 1, 3)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test integer mixed with other tokens (keywords, identifiers)
    {
        Lexer lexer("var age = 25");
         std::vector<Token> expected = {
            Token(TokenType::Var, "var", 1, 1),
            Token(TokenType::Identifier, "age", 1, 5),
            Token(TokenType::Assign, "=", 1, 9),
            Token(TokenType::IntegerLiteral, "25", 1, 11),
            Token(TokenType::EndOfFile, "", 1, 13)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test integer followed by semicolon
    {
        Lexer lexer("10;");
        std::vector<Token> expected = {
            Token(TokenType::IntegerLiteral, "10", 1, 1),
            Token(TokenType::Semicolon, ";", 1, 3),
            Token(TokenType::EndOfFile, "", 1, 4)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }
}

// Test case for recognizing basic operators = and ;
TEST_CASE(TestLexerBasicOperators) {
    // Test individual operators
    {
        Lexer lexer("=;");
        std::vector<Token> expected = {
            Token(TokenType::Assign, "=", 1, 1),
            Token(TokenType::Semicolon, ";", 1, 2),
            Token(TokenType::EndOfFile, "", 1, 3)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test operators with whitespace
    {
        Lexer lexer(" = ; ");
        std::vector<Token> expected = {
            Token(TokenType::Assign, "=", 1, 2),
            Token(TokenType::Semicolon, ";", 1, 4),
            Token(TokenType::EndOfFile, "", 1, 6)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }

    // Test a simple statement
    {
        Lexer lexer("var x = 5;");
        std::vector<Token> expected = {
            Token(TokenType::Var, "var", 1, 1),
            Token(TokenType::Identifier, "x", 1, 5),
            Token(TokenType::Assign, "=", 1, 7),
            Token(TokenType::IntegerLiteral, "5", 1, 9),
            Token(TokenType::Semicolon, ";", 1, 10),
            Token(TokenType::EndOfFile, "", 1, 11)
        };
        std::vector<Token> actual;
        Token tok;
        do {
            tok = lexer.nextToken();
            actual.push_back(tok);
        } while (tok.type != TokenType::EndOfFile);
        assertTokensEqual(actual, expected);
    }
}

// Test case for recognizing more operators (+, -, *, /, !, <, >, ==, !=, <=, >=)
TEST_CASE(TestLexerMoreOperators) {
    std::string input = "+-*/ ! < >\n== != <= >=";
    std::vector<Token> expected = {
        Token(TokenType::Plus, "+", 1, 1),
        Token(TokenType::Minus, "-", 1, 2),
        Token(TokenType::Asterisk, "*", 1, 3),
        Token(TokenType::Slash, "/", 1, 4),
        Token(TokenType::Bang, "!", 1, 6),
        Token(TokenType::LessThan, "<", 1, 8),
        Token(TokenType::GreaterThan, ">", 1, 10),
        Token(TokenType::Equal, "==", 2, 1),
        Token(TokenType::NotEqual, "!=", 2, 4),
        Token(TokenType::LessThanOrEqual, "<=", 2, 7),
        Token(TokenType::GreaterThanOrEqual, ">=", 2, 10),
        Token(TokenType::EndOfFile, "", 2, 12)
    };

    Lexer lexer(input);
    std::vector<Token> actual;
    Token tok;
    do {
        tok = lexer.nextToken();
        actual.push_back(tok);
    } while (tok.type != TokenType::EndOfFile);
    assertTokensEqual(actual, expected);
}

// Test case for recognizing delimiters (, : ( ) { } [ ] .)
TEST_CASE(TestLexerDelimiters) {
    std::string input = ",:(){ }[] .";
    std::vector<Token> expected = {
        Token(TokenType::Comma, ",", 1, 1),
        Token(TokenType::Colon, ":", 1, 2),
        Token(TokenType::LParen, "(", 1, 3),
        Token(TokenType::RParen, ")", 1, 4),
        Token(TokenType::LBrace, "{", 1, 5),
        Token(TokenType::RBrace, "}", 1, 7), // Note space skipped
        Token(TokenType::LBracket, "[", 1, 8),
        Token(TokenType::RBracket, "]", 1, 9),
        Token(TokenType::Dot, ".", 1, 11), // Note space skipped
        Token(TokenType::EndOfFile, "", 1, 12)
    };

    Lexer lexer(input);
    std::vector<Token> actual;
    Token tok;
    do {
        tok = lexer.nextToken();
        actual.push_back(tok);
    } while (tok.type != TokenType::EndOfFile);
    assertTokensEqual(actual, expected);
}

// Test case for a sequence involving various tokens
TEST_CASE(TestLexerSequence) {
     // Updated input to include delimiters and keywords that should now be recognized
     std::string input = "var result = (5 + 10) * 2;\nif (result >= 20) { x = !true; }";
     std::vector<Token> expected = {
        Token(TokenType::Var, "var", 1, 1),
        Token(TokenType::Identifier, "result", 1, 5),
        Token(TokenType::Assign, "=", 1, 12),
        Token(TokenType::LParen, "(", 1, 14),
        Token(TokenType::IntegerLiteral, "5", 1, 15),
        Token(TokenType::Plus, "+", 1, 17),
        Token(TokenType::IntegerLiteral, "10", 1, 19),
        Token(TokenType::RParen, ")", 1, 21),
        Token(TokenType::Asterisk, "*", 1, 23),
        Token(TokenType::IntegerLiteral, "2", 1, 25),
        Token(TokenType::Semicolon, ";", 1, 26),
        Token(TokenType::If, "if", 2, 1), // Line 2
        Token(TokenType::LParen, "(", 2, 4),
        Token(TokenType::Identifier, "result", 2, 5),
        Token(TokenType::GreaterThanOrEqual, ">=", 2, 12),
        Token(TokenType::IntegerLiteral, "20", 2, 15),
        Token(TokenType::RParen, ")", 2, 17),
        Token(TokenType::LBrace, "{", 2, 19),
        Token(TokenType::Identifier, "x", 2, 21),
        Token(TokenType::Assign, "=", 2, 23),
        Token(TokenType::Bang, "!", 2, 25),
        Token(TokenType::True, "true", 2, 26),
        Token(TokenType::Semicolon, ";", 2, 30),
        Token(TokenType::RBrace, "}", 2, 32),
        Token(TokenType::EndOfFile, "", 2, 33)
    };

    Lexer lexer(input);
    std::vector<Token> actual;
    Token tok;
    do {
        tok = lexer.nextToken();
        actual.push_back(tok);
    } while (tok.type != TokenType::EndOfFile);
    assertTokensEqual(actual, expected);
}
