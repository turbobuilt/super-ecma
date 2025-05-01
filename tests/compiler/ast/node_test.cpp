#include "compiler/ast/node.h" // Include the header for the Node interface
#include "test_runner.h"       // Include the test runner utilities
#include <string>
#include <memory>

// A minimal concrete class derived from Node for testing purposes.
// We cannot instantiate Node directly because it's abstract.
class DummyNode : public Node {
public:
    std::string tokenLiteral() const override {
        return "dummy_token";
    }

    std::string toString() const override {
        return "DummyNode[dummy_token]";
    }
};

// Test case to verify the base Node interface and its requirements.
TEST_CASE(TestBaseNodeInterface) {
    // Create an instance of the dummy derived class.
    DummyNode dummy;

    // Test the virtual methods inherited from Node.
    ASSERT_EQ(dummy.tokenLiteral(), "dummy_token");
    ASSERT_EQ(dummy.toString(), "DummyNode[dummy_token]");

    // Test polymorphism (optional but good practice).
    // Create a pointer to the base class Node pointing to the derived object.
    std::unique_ptr<Node> nodePtr = std::make_unique<DummyNode>();

    // Verify that calling the virtual methods through the base pointer
    // correctly invokes the derived class's implementation.
    ASSERT_EQ(nodePtr->tokenLiteral(), "dummy_token");
    ASSERT_EQ(nodePtr->toString(), "DummyNode[dummy_token]");

    // The unique_ptr will automatically handle deletion, testing the virtual destructor implicitly.
}
