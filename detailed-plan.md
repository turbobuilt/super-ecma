# SuperECMA Detailed Implementation Plan (C++)

This plan breaks down the SuperECMA implementation into small, verifiable, and testable tasks. Each task typically involves creating/modifying one source file and a corresponding test file.

**Completed Tasks:**

*   Task 1: Project Setup & Test Runner
*   Task 2: Define Token Types
*   Task 3: Basic Token Structure
*   Task 4: Lexer Core & EOF
*   Task 5: Lexer Whitespace Skipping
*   **Task 6: Lexer Keyword Recognition (`var`)**

**Current Task:**

*   **Task 7: Lexer Identifier Recognition**

**Upcoming Tasks:**

*   Task 8: Lexer Integer Literal Recognition
*   Task 9: Lexer Basic Operators (`=`, `;`)
*   Task 10: Base AST Node
*   Task 11: AST Literal Nodes
*   Task 12: AST Identifier Node
*   Task 13: AST Variable Declaration Node
*   Task 14: Parser Core & Basic Setup
*   Task 15: Parse Variable Declaration (No Initializer)
*   Task 16: Parse Integer Literal Expression
*   Task 17: Parse Variable Declaration (With Integer Initializer)
*   *(... More tasks will be added as development progresses)*

---

## Task Details

### Task 1: Project Setup & Test Runner

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

### Task 2: Define Token Types

*   **Goal:** Define all necessary token types for the language lexer.
*   **Source File:** `src/compiler/lexer/token_types.h`
*   **Description:** Create an enum class `TokenType` defining all required tokens:
    *   `EndOfFile`, `Illegal`
    *   `Identifier`, `IntegerLiteral`, `FloatLiteral`, `StringLiteral`
    *   Keywords: `Var`, `Wild`, `Run`, `Destroy`, `Ref`, `Capture`, `Transfer`, `Defer`, `Using`, `Function`, `Return`, `If`, `Else`, `For`, `While`, `True`, `False`, `Null`, `Int`, `Float`, `String` (add more as needed from `lang.md`)
    *   Operators: `Assign` (`=`), `Plus` (`+`), `Minus` (`-`), `Asterisk` (`*`), `Slash` (`/`), `Bang` (`!`), `LessThan` (`<`), `GreaterThan` (`>`), `Equal` (`==`), `NotEqual` (`!=`), `LessThanOrEqual` (`<=`), `GreaterThanOrEqual` (`>=`)
    *   Delimiters: `Comma` (`,`), `Semicolon` (`;`), `Colon` (`:`), `LParen` (`(`), `RParen` (`)`), `LBrace` (`{`), `RBrace` (`}`), `LBracket` (`[`), `RBracket` (`]`), `Dot` (`.`)
    *   Add a helper function `std::string tokenTypeToString(TokenType type)` for debugging/testing.
*   **Test File:** `tests/compiler/lexer/token_types_test.cpp`
*   **Test Cases:**
    *   Include `token_types.h`.
    *   Call `tokenTypeToString` for a few representative token types (e.g., `TokenType::Var`, `TokenType::Identifier`, `TokenType::Assign`, `TokenType::EndOfFile`) and assert that the returned string matches the expected name (e.g., `"Var"`, `"Identifier"`, `"Assign"`, `"EndOfFile"`). This verifies the enum values and the helper function.
*   **Verification:** Compile and run the tests. The `token_types_test` should pass.

### Task 3: Basic Token Structure

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

### Task 4: Lexer Core & EOF

*   **Goal:** Create the basic `Lexer` class structure and implement the ability to recognize the end of the input.
*   **Source File:** `src/compiler/lexer/lexer.h`, `src/compiler/lexer/lexer.cpp`
*   **Description:**
    *   Define a `Lexer` class in `lexer.h`.
    *   It should take the source code (`std::string_view`) as input in its constructor.
    *   Keep track of the current position (`position`), read position (`readPosition`), and current character (`ch`). Initialize `ch` by calling `readChar()` in the constructor.
    *   Implement a `readChar()` method to advance the position and update `ch`. Handle reaching the end of the input by setting `ch` to `0` (NUL character).
    *   Implement a `nextToken()` method. For this task, it should only return an `EndOfFile` token (with type `TokenType::EndOfFile` and an empty literal) when `ch` is `0`. If `ch` is not `0`, return an `Illegal` token for now and advance using `readChar()`.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Create a `Lexer` instance with an empty string `""`.
    *   Call `nextToken()`. Assert that the returned token has `type == TokenType::EndOfFile`.
    *   Create a `Lexer` instance with a non-empty string like `"abc"`. Call `nextToken()` repeatedly until it returns `EndOfFile`. Assert the final token is correct.
*   **Verification:** Compile and run the tests using `./test.sh`. The `TestLexerEOF` test case should pass.

### Task 5: Lexer Whitespace Skipping

*   **Goal:** Implement the ability for the `Lexer` to skip whitespace characters.
*   **Source File:** `src/compiler/lexer/lexer.h`, `src/compiler/lexer/lexer.cpp`
*   **Description:** Extend the `Lexer` class to recognize and skip whitespace characters (`' '`, `'\t'`, `'\n'`, `'\r'`) during tokenization.
    *   Add a `skipWhitespace()` method to the `Lexer` class.
    *   This method should consume characters like space (`' '`), tab (`'\t'`), newline (`'\n'`), and carriage return (`'\r'`).
    *   Call `skipWhitespace()` at the beginning of `nextToken()`.
*   **Test File:** `tests/compiler/lexer/lexer_test.cpp`
*   **Test Cases:**
    *   Create a `Lexer` instance with a string containing only whitespace (e.g., `"   \t\n\r"`). Call `nextToken()`. Assert that the returned token is `EndOfFile`.
    *   Create a `Lexer` instance with a string containing tokens separated by whitespace (e.g., `" a b "`). Call `nextToken()` repeatedly and assert that the tokens are recognized correctly (or `Illegal` for now) and the final token is `EndOfFile`.
*   **Verification:** Compile and run the tests using `./test.sh`. The `TestLexerWhitespaceSkipping` test case should pass.

### Task 6: Lexer Keyword Recognition (`var`)

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

*(Add subsequent tasks here following the same pattern)*
