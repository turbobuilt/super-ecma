#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept> // Required for std::runtime_error

// Define a type for test functions
using TestFunc = std::function<void()>;

// Structure to hold test case information
struct TestCase {
    std::string name;
    TestFunc func;
};

// Global registry for test cases
inline std::vector<TestCase>& GetTestRegistry() {
    static std::vector<TestCase> registry;
    return registry;
}

// Function to register a test case
inline bool RegisterTest(const std::string& name, TestFunc func) {
    GetTestRegistry().push_back({name, func});
    return true;
}

// Macro to simplify test case registration
#define TEST_CASE(name) \
    void name(); \
    static bool name##_registered = RegisterTest(#name, name); \
    void name()

// Assertion Macros
#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        throw std::runtime_error("Assertion failed: " #condition " is false at " __FILE__ ":" + std::to_string(__LINE__)); \
    }

#define ASSERT_FALSE(condition) \
    if ((condition)) { \
        throw std::runtime_error("Assertion failed: " #condition " is true at " __FILE__ ":" + std::to_string(__LINE__)); \
    }

#define ASSERT_EQ(a, b) \
    if (!((a) == (b))) { \
        throw std::runtime_error("Assertion failed: " #a " == " #b " (" + std::to_string(a) + " vs " + std::to_string(b) + ") at " __FILE__ ":" + std::to_string(__LINE__)); \
    }
// Add more ASSERT macros as needed (e.g., ASSERT_NE, ASSERT_THROW)

// Function to run all registered tests
int RUN_ALL_TESTS();

#endif // TEST_RUNNER_H
