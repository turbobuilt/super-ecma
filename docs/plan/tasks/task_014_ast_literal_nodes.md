# Task 14: AST Literal Nodes

*   **Goal:** Define AST nodes for integer, float, and string literals.
*   **Source File:** `src/compiler/ast/expression.h`
*   **Description:**
    *   Define a base `Expression` class inheriting from `Node`. Add a dummy `expressionNode()` pure virtual method.
    *   Define `IntegerLiteral` inheriting from `Expression`. Store the `Token` and the `int64_t` value. Implement `tokenLiteral()` and `toString()`.
    *   Define `FloatLiteral` inheriting from `Expression`. Store the `Token` and the `double` value. Implement `tokenLiteral()` and `toString()`.
    *   Define `StringLiteral` inheriting from `Expression`. Store the `Token` and the `std::string` value. Implement `tokenLiteral()` and `toString()`.
*   **Test File:** `tests/compiler/ast/expression_test.cpp`
*   **Test Cases:**
    *   Add `TestIntegerLiteralNode`.
    *   Add `TestFloatLiteralNode`.
    *   Add `TestStringLiteralNode`.
    *   For each, create a sample `Token`, instantiate the corresponding node, and verify its `tokenLiteral()`, `toString()`, and stored `value`.
*   **Verification:** Compile and run tests. The new tests should pass.
