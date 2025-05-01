# Task 12: Refactor Lexer Implementation

*   **Goal:** Review and improve the existing lexer code for clarity, correctness, and potential performance.
*   **Source Files:** `src/compiler/lexer/lexer.h`, `src/compiler/lexer/lexer.cpp`, `src/compiler/lexer/token_types.h`
*   **Description:**
    *   Review the `nextToken()` logic. Can the `switch` statement be improved?
    *   Implement proper line/column tracking. Update `Lexer` members and `nextToken` logic to increment line/column counts correctly.
    *   Review helper functions (`readIdentifier`, `readNumber`, `skipWhitespace`, `peekChar`, etc.). Are they efficient and correct?
    *   Check error handling. Is `TokenType::Illegal` used appropriately?
    *   Ensure consistency in coding style and naming.
    *   Look for opportunities to reduce code duplication.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   No *new* tests are strictly required, but ensure all existing lexer tests still pass after refactoring.
    *   Update existing tests to assert correct line/column positions for tokens.
*   **Verification:** Compile and run tests. All lexer tests should pass. The code should be demonstrably cleaner or more correct, and line/column tracking should be functional.
