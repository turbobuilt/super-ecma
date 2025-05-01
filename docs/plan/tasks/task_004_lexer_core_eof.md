# Task 4: Lexer Core & EOF

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
