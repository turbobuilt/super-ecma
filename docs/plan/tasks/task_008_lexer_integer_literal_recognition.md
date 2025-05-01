# Task 8: Lexer Integer Literal Recognition

*   **Goal:** Implement recognition of integer literals (sequences of digits).
*   **Source File:** `src/compiler/lexer/lexer.h`, `src/compiler/lexer/lexer.cpp`
*   **Description:**
    *   Add a `readNumber()` method to the `Lexer` class. This method should consume a sequence of digits.
    *   Modify `nextToken()` to check for digits using `isDigit()`. If a digit is found, call `readNumber()` and return an `IntegerLiteral` token.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Add `TestLexerIntegerLiteral`.
    *   Test inputs like `"123"`, `"0"`, `" 99 "`. Expect `TokenType::IntegerLiteral` with the correct literal value.
    *   Test integers mixed with other tokens (e.g., `"var x = 5;"`).
*   **Verification:** Compile and run tests. `TestLexerIntegerLiteral` should pass.
