# Task 3: Basic Token Structure

*   **Goal:** Define a structure to hold token information (type, literal value, location).
*   **Source File:** `src/compiler/lexer/token.h`
*   **Description:**
    *   Include `token_types.h`.
    *   Define a `struct Token` containing:
        *   `TokenType type`
        *   `std::string literal` (the actual text/lexeme)
        *   `int line` (optional, for error reporting, 1-based)
        *   `int column` (optional, for error reporting, 1-based)
    *   Provide a constructor for easy initialization.
    *   Add an `operator==` for easy comparison in tests.
*   **Test File:** `tests/compiler/lexer/token_test.cpp`
*   **Test Cases:**
    *   Include `token.h`.
    *   Create several `Token` instances (e.g., `Token{TokenType::Var, "var", 1, 1}`, `Token{TokenType::Identifier, "myVar", 1, 5}`, `Token{TokenType::IntegerLiteral, "123", 2, 1}`).
    *   Assert that the `type`, `literal`, `line`, and `column` members of the created tokens match the expected values.
    *   Test the `operator==`.
*   **Verification:** Compile and run the tests. The `token_test` should pass.
