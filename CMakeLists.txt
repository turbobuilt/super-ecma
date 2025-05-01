cmake_minimum_required(VERSION 3.10)
project(SuperEcma CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find source files
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/compiler/lexer/*.cpp")
# Separate test sources explicitly
file(GLOB TEST_RUNNER_SRC "tests/test_runner.cpp" "tests/test_runner_test.cpp")
file(GLOB TEST_MAIN_SRC "tests/main.cpp")
# Find future test case files
file(GLOB_RECURSE TEST_CASE_FILES "tests/compiler/*.cpp" "tests/compiler/lexer/*.cpp" "tests/runtime/*.cpp" "tests/tools/*.cpp")

# Add executable for the main program
add_executable(superecma ${SRC_FILES})
# Ensure compiler headers are found
target_include_directories(superecma PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add executable for tests
add_executable(run_tests ${TEST_MAIN_SRC} ${TEST_RUNNER_SRC} ${TEST_CASE_FILES} ${SRC_FILES}) # Include SRC_FILES needed by tests
# Ensure test runner header and compiler headers are found
target_include_directories(run_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries if needed (example)
# target_link_libraries(superecma PRIVATE some_library)
# target_link_libraries(run_tests PRIVATE some_library)

# Enable testing
enable_testing()

# Add tests using CTest
add_test(NAME UnitTests COMMAND run_tests)
