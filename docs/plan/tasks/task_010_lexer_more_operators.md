# Task 10: Lexer More Operators (`+`, `-`, `*`, `/`, `!`, `<`, `>`, `==`, `!=`, `<=`, `>=`)

*   **Goal:** Implement recognition for common single and double-character operators.
*   **Source File:** `src/compiler/lexer/lexer.cpp`, `src/compiler/lexer/lexer.h` (added `peekChar()`)
*   **Description:**
    *   Extended `nextToken()` to handle `+`, `-`, `*`, `/`, `!`, `<`, `>`.
    *   Implemented lookahead using `peekChar()` to handle two-character operators `==`, `!=`, `<=`, `>=`.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Added `TestLexerMoreOperators`.
    *   Tested each operator individually and in sequences.
*   **Verification:** Compile and run tests. `TestLexerMoreOperators` should pass.
