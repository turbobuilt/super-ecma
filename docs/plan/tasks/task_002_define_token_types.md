# Task 2: Define Token Types

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
