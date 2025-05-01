# Task 13: Base AST Node

*   **Goal:** Define a base `Node` interface/class for the Abstract Syntax Tree (AST).
*   **Source File:** `src/compiler/ast/node.h`
*   **Description:**
    *   Created `src/compiler/ast/` directory.
    *   Defined a base abstract `Node` class in `node.h`.
    *   Included a virtual destructor.
    *   Defined pure virtual functions `tokenLiteral()` and `toString()`.
*   **Test File:** `tests/compiler/ast/node_test.cpp`
*   **Test Cases:**
    *   Created `tests/compiler/ast/` directory.
    *   Added `TestBaseNodeInterface`.
    *   Created a minimal concrete derived class `DummyNode` within the test file to verify the interface requirements and compilation.
*   **Verification:** Compile and run tests. `TestBaseNodeInterface` should pass.
