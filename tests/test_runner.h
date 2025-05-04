#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept> // Required for std::runtime_error
#include <sstream>   // Include for std::ostringstream

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
        std::ostringstream oss; \
        oss << "Assertion failed: " #a " == " #b " ("; \
        oss << (a) << " vs " << (b); \
        oss << ") at " __FILE__ ":" << __LINE__; \
        throw std::runtime_error(oss.str()); \
    }

#define ASSERT_NE(a, b) \
    if (!((a) != (b))) { \
        std::ostringstream oss; \
        oss << "Assertion failed: " #a " != " #b " ("; \
        oss << (a) << " vs " << (b); \
        oss << ") at " __FILE__ ":" << __LINE__; \
        throw std::runtime_error(oss.str()); \
    }

// Function to run all registered tests
int RUN_ALL_TESTS();

#endif // TEST_RUNNER_H
