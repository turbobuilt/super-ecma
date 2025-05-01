# Task 1: Project Setup & Test Runner

*   **Goal:** Establish the basic directory structure and create a minimal test runner framework.
*   **Source File:** `tests/test_runner.cpp`, `tests/test_runner.h`
*   **Description:**
    *   Create directories: `src/`, `tests/`, `src/compiler/`, `src/compiler/lexer/`, `tests/compiler/`, `tests/compiler/lexer/`.
    *   Implement a simple C++ test runner in `test_runner.h` and `test_runner.cpp`. This could involve:
        *   A way to register test functions (e.g., using a macro or a registry).
        *   A `RUN_ALL_TESTS()` function.
        *   Basic assertion macros (e.g., `ASSERT_TRUE(condition)`, `ASSERT_EQ(a, b)`).
        *   Simple output indicating test names and pass/fail status.
*   **Test File:** `tests/main.cpp` (Entry point), `tests/test_runner_test.cpp`
*   **Test Cases:**
    *   `tests/main.cpp`: Contains the `main` function that calls `RUN_ALL_TESTS()`.
    *   `tests/test_runner_test.cpp`:
        *   Define a test case `TestRunnerSelfCheck` using the runner's registration mechanism.
        *   Inside the test case, use `ASSERT_TRUE(true)` and `ASSERT_EQ(1, 1)` to verify the runner works for passing conditions.
        *   (Optional) Add tests that are expected to fail to see the failure output, perhaps conditionally compiled out later.
*   **Verification:** Compile and run `tests/main.cpp`. The output should show the `TestRunnerSelfCheck` test passing.
