# Task 9: Lexer Basic Operators (`=`, `;`)

*   **Goal:** Implement recognition of the assignment (`=`) and semicolon (`;`) operators.
*   **Source File:** `src/compiler/lexer/lexer.cpp`
*   **Description:**
    *   Modify `nextToken()` to check for `=` and `;`.
    *   If `=` is found, return a token with `TokenType::Assign` and literal `"="`.
    *   If `;` is found, return a token with `TokenType::Semicolon` and literal `";"`.
    *   Remember to call `readChar()` after recognizing the operator to advance the position.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Add `TestLexerBasicOperators`.
    *   Test input `"="`. Expect `TokenType::Assign`.
    *   Test input `";"`. Expect `TokenType::Semicolon`.
    *   Test input `" = ; "`. Expect `Assign`, `Semicolon`, `EndOfFile`.
    *   Test input `"var x = 5;"`. Expect `Var`, `Identifier`, `Assign`, `IntegerLiteral`, `Semicolon`, `EndOfFile`.
*   **Verification:** Compile and run tests. `TestLexerBasicOperators` should pass.
