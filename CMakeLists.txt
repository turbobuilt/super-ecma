cmake_minimum_required(VERSION 3.10)
project(SuperEcma CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing globally
enable_testing()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Add tests using CTest (targets defined in subdirectories)
# The COMMAND 'run_tests' should match the executable target name defined in tests/CMakeLists.txt
add_test(NAME UnitTests COMMAND run_tests)
