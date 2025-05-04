# Define the library target
add_library(superecma_lib STATIC
    # List all source files for the library explicitly
    main.cpp # Keep main.cpp if it contains core logic needed by tests, otherwise move it or exclude it
    compiler/lexer/lexer.cpp
    compiler/parser/parser.cpp
    # compiler/ast/ast_nodes.cpp # Add other source files as needed
    # compiler/token/token.cpp   # Add other source files as needed
)

# Specify public include directories for the library
# This allows targets linking against this library (like tests)
# to find headers using paths relative to the src directory
target_include_directories(superecma_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add dependencies if needed (e.g., external libraries)
# target_link_libraries(superecma_lib PRIVATE some_dependency)
