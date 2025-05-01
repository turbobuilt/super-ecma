# AI Instructions for SuperECMA Development

Your primary goal is to implement the SuperECMA language step-by-step, following the tasks outlined in `detailed-plan.md`.

**Directory Structure:**

*   Source files: `src/{feature}/file.cpp`
*   Test files: `tests/{feature}/file.test.cpp`

**Core Workflow:**

1.  **Identify the Current Task:** Look at the "Current Task" section in `detailed-plan.md` and `checklist.md`.
2.  **Perform ONE Task:** Execute *only* the single, currently designated task.
    *   This usually involves creating or modifying one primary source file (e.g., in `src/compiler/lexer.cpp`) and one corresponding test file (e.g., in `tests/compiler/lexer_test.cpp`).
    *   Adhere strictly to the requirements specified for that task in `detailed-plan.md`.
    *   Focus on the smallest possible verifiable step.
3.  **Generate Code:** Provide the necessary C++ code for the source and test files. Use the standard format (filepath comment, concise changes).
4.  **Update `testprogram.ses`:** If the task successfully implements new language syntax, add examples of that syntax to `testprogram.ses`. This file serves as a running log of supported features for the `run.sh` script.
5.  **Update Plan & Checklist:**
    *   Modify `detailed-plan.md`: Move the completed task to the "Completed Tasks" list and update the "Current Task" to the next one in the "Upcoming Tasks" list.
    *   Modify `checklist.md`: Mark the completed task with `[x]` and indicate the new "Current" task.
6.  **Stop:** Do not proceed to the next task until requested again. Wait for the user to verify and test the changes.

**Important Rules:**

*   **One Task at a Time:** Absolutely critical. Do not combine tasks.
*   **Testability:** Ensure each task results in code that can be compiled and tested. The test file created/modified in the task should verify the functionality added/changed in the source file.
*   **Use Wisdome:** The goal is to make a great product built for performance, conciseness, and a clear, simple, logical structure. That means sometimes you may realize that some of the tasks we came up with at the beginning are not correct. When you realize we need to do it a bit different or maybe a task will be more complicated than we thought, please update the task list with new tasks..
*   **Conciseness:** We want to make the code concise if possible, to preserve tokens. However, make sure not to take shortcuts that will lead to degraded performance.
*   **File Paths:** Use the correct file paths as specified in the plan or existing file structure (e.g., `src/compiler/lexer.cpp`, `tests/compiler/lexer_test.cpp`).
