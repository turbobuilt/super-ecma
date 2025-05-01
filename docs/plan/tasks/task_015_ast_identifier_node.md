# Task 15: AST Identifier Node

*   **Goal:** Define an AST node for identifiers (variable names, function names, etc.).
*   **Source File:** `src/compiler/ast/expression.h`
*   **Description:**
    *   Define an `Identifier` class inheriting from `Expression`.
    *   Store the `Token` (which should have `TokenType::Identifier`).
    *   Store the identifier's name/value as a `std::string`.
    *   Implement `tokenLiteral()` and `toString()`. The `toString()` should return the identifier's name.
*   **Test File:** `tests/compiler/ast/expression_test.cpp`
*   **Test Cases:**
    *   Add `TestIdentifierNode`.
    *   Create a sample `Identifier` token (e.g., `myVar`).
    *   Instantiate the `Identifier` node.
    *   Verify its `tokenLiteral()`, `toString()`, and stored `value`.
*   **Verification:** Compile and run tests. The new test should pass.
