#include "test_runner.h"

// A simple test case to verify the basic assertion macros work.
TEST_CASE(TestRunnerSelfCheck) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
    ASSERT_EQ(1, 1);
    ASSERT_EQ(5 * 5, 25);
    // ASSERT_EQ(1, 2); // Uncomment this line to test failure reporting
}

// Add more tests for the runner if needed
// TEST_CASE(AnotherTestRunnerFeature) {
//     // ... test other aspects ...
// }
