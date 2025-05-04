# CMakeLists.txt for tests

# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(SuperECMA_Tests)

# Enable testing
enable_testing()

# Include directories
include_directories(../src)

# Define the executable for running tests
add_executable(run_tests
    # List all test source files explicitly
    main.cpp
    test_runner.cpp
    test_runner_test.cpp
    compiler/ast/expression_test.cpp
    compiler/ast/node_test.cpp
    compiler/ast/statement_test.cpp
    compiler/lexer/lexer_test.cpp
    compiler/lexer/token_test.cpp
    compiler/lexer/token_types_test.cpp
    compiler/parser/parser_test.cpp
    # Add other test source files here explicitly
)

# Link the test runner against the main library
# The library target 'superecma_lib' is defined in src/CMakeLists.txt
target_link_libraries(run_tests PRIVATE superecma_lib)

# Include directories needed for the tests
target_include_directories(run_tests PRIVATE
    # Access test headers like test_runner.h
    ${CMAKE_CURRENT_SOURCE_DIR}
    # Access library headers from the src directory
    # The path is relative to the top-level CMakeLists.txt
    ${CMAKE_SOURCE_DIR}/src
)

# Enable testing with CTest
include(CTest)
add_test(NAME RunAllTests COMMAND run_tests)