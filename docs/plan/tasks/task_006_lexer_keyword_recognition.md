# Task 6: Lexer Keyword Recognition (`var`)

*   **Goal:** Implement recognition of the `var` keyword.
*   **Source File:** `src/compiler/lexer/lexer.h`, `src/compiler/lexer/lexer.cpp`, `src/compiler/lexer/token_types.h`
*   **Description:** Extend the `Lexer` to recognize identifiers and check if they match known keywords.
    *   Add helper methods `isLetter()` and `readIdentifier()` to `Lexer`.
    *   Add a keyword map and `lookupIdentifier()` function in `token_types.h`.
    *   Modify `nextToken()` to call `readIdentifier()` when a letter is encountered and use `lookupIdentifier()` to determine if it's `TokenType::Var` or `TokenType::Identifier`.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Add `TestLexerVarKeyword`.
    *   Test input `"var"`. Expect `TokenType::Var`.
    *   Test input `" variable "`. Expect `TokenType::Identifier`.
    *   Test input `"v"`. Expect `TokenType::Identifier`.
*   **Verification:** Compile and run tests. `TestLexerVarKeyword` should pass.
