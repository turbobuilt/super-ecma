# Task 5: Lexer Whitespace Skipping

*   **Goal:** Implement the ability for the `Lexer` to skip whitespace characters.
*   **Source File:** `src/compiler/lexer/lexer.h`, `src/compiler/lexer/lexer.cpp`
*   **Description:** Extend the `Lexer` class to recognize and skip whitespace characters (`' '`, `'\t'`, `'\n'`, `'\r'`) during tokenization.
    *   Add a `skipWhitespace()` method to the `Lexer` class.
    *   This method should consume characters like space (`' '`), tab (`'\t'`), newline (`'\n'`), and carriage return (`'\r'`).
    *   Call `skipWhitespace()` at the beginning of `nextToken()`.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Create a `Lexer` instance with a string containing only whitespace (e.g., `"   \t\n\r"`). Call `nextToken()`. Assert that the returned token is `EndOfFile`.
    *   Create a `Lexer` instance with a string containing tokens separated by whitespace (e.g., `" a b "`). Call `nextToken()` repeatedly and assert that the tokens are recognized correctly (or `Illegal` for now) and the final token is `EndOfFile`.
*   **Verification:** Compile and run the tests using `./test.sh`. The `TestLexerWhitespaceSkipping` test case should pass.
