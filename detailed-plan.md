# SuperECMA Detailed Implementation Plan (C++)

This plan breaks down the SuperECMA implementation into small, verifiable, and testable tasks. Each task typically involves creating/modifying one source file and a corresponding test file. Detailed descriptions for each task can be found in the `docs/plan/tasks/` directory (e.g., `docs/plan/tasks/task_001_project_setup.md`).

**Note on Refactoring:** Periodically, "Refactor" tasks will be included. These tasks are opportunities to review the code written so far, improve its structure, enhance performance, increase clarity, or fix any identified inconsistencies without adding new features.

**Completed Tasks:**

*   Task 1: Project Setup & Test Runner
*   Task 2: Define Token Types
*   Task 3: Basic Token Structure
*   Task 4: Lexer Core & EOF
*   Task 5: Lexer Whitespace Skipping
*   Task 6: Lexer Keyword Recognition (`var`)
*   Task 7: Lexer Identifier Recognition
*   Task 8: Lexer Integer Literal Recognition
*   Task 9: Lexer Basic Operators (`=`, `;`)
*   Task 10: Lexer More Operators (`+`, `-`, `*`, `/`, `!`, `<`, `>`, `==`, `!=`, `<=`, `>=`)
*   Task 11: Lexer Delimiters (`,`, `:`, `(`, `)`, `{`, `}`, `[`, `]`, `.`)
*   Task 12: Refactor Lexer Implementation (Review tokenization logic, position tracking, helper functions)
*   Task 13: Base AST Node (Define base `Node` interface/class for the Abstract Syntax Tree)
*   Task 14: AST Literal Nodes (Define nodes for integer, float, string literals)
*   Task 15: AST Identifier Node
*   Task 16: AST Variable Declaration Node
*   Task 17: Parser Core & Basic Setup
*   Task 18: Parse String Literal Expression
*   Task 19: Parse Function Call Expression (Simple, e.g., `print(...)`)

**Current Task:**

*   **Task 20: Basic Interpreter/Runtime Setup (Placeholder execution)**

**Upcoming Tasks:**

*   Task 21: Implement Built-in `print` Function (Output to console)
*   Task 22: Parse Basic Program Structure (Sequence of statements/expressions)
*   Task 23: Parse Variable Declaration (No Initializer)
*   Task 24: Parse Integer Literal Expression
*   Task 25: Parse Variable Declaration (With Integer Initializer)
*   *(... More tasks will be added as development progresses)*

---

*(Add subsequent tasks here following the same pattern, potentially adding more Refactor tasks after major milestones like Parser completion)*
