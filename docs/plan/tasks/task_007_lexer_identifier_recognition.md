# Task 7: Lexer Identifier Recognition

*   **Goal:** Implement recognition of identifiers (sequences of letters, digits, and underscores, starting with a letter or underscore).
*   **Source File:** `src/compiler/lexer/lexer.cpp`
*   **Description:**
    *   Update the `readIdentifier()` method in `Lexer` to consume letters, digits, and underscores. Ensure it correctly handles the start condition (letter or underscore).
    *   Ensure `nextToken()` correctly uses the updated `readIdentifier()`.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Add `TestLexerIdentifierRecognition`.
    *   Test inputs like `"myVar"`, `"another_var"`, `"_leadingUnderscore"`, `"var123"`. Expect `TokenType::Identifier` with the correct literal.
    *   Test identifiers mixed with whitespace and keywords.
*   **Verification:** Compile and run tests. `TestLexerIdentifierRecognition` should pass.
