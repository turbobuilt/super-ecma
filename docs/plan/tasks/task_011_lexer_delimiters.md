# Task 11: Lexer Delimiters (`,`, `:`, `(`, `)`, `{`, `}`, `[`, `]`, `.`)

*   **Goal:** Implement recognition for common delimiter characters.
*   **Source File:** `src/compiler/lexer/lexer.cpp`
*   **Description:**
    *   Extended `nextToken()` to handle `,`, `:`, `(`, `)`, `{`, `}`, `[`, `]`, `.`.
    *   Returned the corresponding `TokenType` (e.g., `Comma`, `Colon`, `LParen`, etc.).
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Added `TestLexerDelimiters`.
    *   Tested each delimiter individually.
    *   Tested sequences like `"function(a, b) { return a.x; }"` (Note: `function` keyword needs to be added to `token_types.h` keyword map for full test pass). Updated `TestLexerSequence`.
*   **Verification:** Compile and run tests. `TestLexerDelimiters` and updated `TestLexerSequence` should pass.
