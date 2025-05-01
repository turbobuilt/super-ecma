#include "test_runner.h"
#include <iostream>
#include <vector>
#include <string>

int RUN_ALL_TESTS() {
    const auto& tests = GetTestRegistry();
    int failed_count = 0;
    int passed_count = 0;

    std::cout << "Running " << tests.size() << " test cases...\n";
    std::cout << "----------------------------------------\n";

    for (const auto& test : tests) {
        std::cout << "[ RUN      ] " << test.name << std::endl;
        try {
            test.func();
            std::cout << "[       OK ] " << test.name << std::endl;
            passed_count++;
        } catch (const std::exception& e) {
            std::cerr << "[  FAILED  ] " << test.name << std::endl;
            std::cerr << "  Error: " << e.what() << std::endl;
            failed_count++;
        } catch (...) {
            std::cerr << "[  FAILED  ] " << test.name << std::endl;
            std::cerr << "  Error: Unknown exception caught." << std::endl;
            failed_count++;
        }
    }

    std::cout << "----------------------------------------\n";
    std::cout << "[==========] " << tests.size() << " tests ran." << std::endl;
    std::cout << "[  PASSED  ] " << passed_count << " tests." << std::endl;
    if (failed_count > 0) {
        std::cout << "[  FAILED  ] " << failed_count << " tests." << std::endl;
    }

    return (failed_count == 0) ? 0 : 1; // Return 0 on success, 1 on failure
}
