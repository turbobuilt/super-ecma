# Task 17: Parser Core & Basic Setup

*   **Goal:** Establish the basic structure for the `Parser` class.
*   **Source Files:** `src/compiler/parser/parser.h`, `src/compiler/parser/parser.cpp`
*   **Description:**
    *   Create the `src/compiler/parser/` directory if it doesn't exist.
    *   Define the `Parser` class in `parser.h`.
    *   Include necessary headers (`lexer/lexer.h`, `lexer/token.h`, `ast/node.h`, `ast/statement.h`, `ast/expression.h`).
    *   The `Parser` should hold a reference to a `Lexer`.
    *   Store the current token (`currentToken`) and the next token (`peekToken`).
    *   Store a list of parsing errors (`std::vector<std::string> errors`).
    *   Implement a constructor `Parser(Lexer& l)` that initializes the lexer reference and calls `nextToken()` twice to populate `currentToken` and `peekToken`.
    *   Implement a private helper method `nextToken()` that advances `currentToken` to `peekToken` and `peekToken` to the next token from the lexer.
    *   Implement a public method `parseProgram()` which will eventually return the root `Program` AST node (for now, it can be minimal or return `nullptr`).
    *   Implement a public method `getErrors()` to retrieve the list of parsing errors.
*   **Test File:** `tests/compiler/parser/parser_test.cpp`
*   **Test Cases:**
    *   Create the `tests/compiler/parser/` directory if it doesn't exist.
    *   Add `TestParserInitialization`.
    *   Instantiate a `Lexer` with a simple input (e.g., `"var x = 5;"`).
    *   Instantiate a `Parser` with the lexer.
    *   Verify that the `Parser` is created without crashing.
    *   (Optional) Check the initial state of `currentToken` and `peekToken` if desired, though this will be more thoroughly tested when parsing specific statements/expressions.
    *   Check that `getErrors()` returns an empty vector initially.
*   **Verification:** Compile and run tests. `TestParserInitialization` should pass.
