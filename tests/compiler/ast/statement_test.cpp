#include "compiler/ast/statement.h"
#include "compiler/ast/expression.h" // Need Identifier, IntegerLiteral etc.
#include "compiler/lexer/token.h"
#include "test_runner.h"
#include <string>
#include <memory>

// Test case for VarStatement node
TEST_CASE(TestVarStatementNode) {
    // Scenario 1: Declaration without initializer (var x;)
    {
        Token varToken(TokenType::Var, "var", 1, 1);
        Token identToken(TokenType::Identifier, "x", 1, 5);
        auto identifier = std::make_unique<Identifier>(identToken, "x");

        // Pass ownership of the identifier unique_ptr
        VarStatement varStmt(varToken, std::move(identifier));

        ASSERT_EQ(varStmt.tokenLiteral(), "var");
        ASSERT_EQ(varStmt.token.type, TokenType::Var);
        ASSERT_TRUE(varStmt.name != nullptr);
        ASSERT_EQ(varStmt.name->value, "x");
        ASSERT_EQ(varStmt.name->tokenLiteral(), "x");
        ASSERT_TRUE(varStmt.value == nullptr); // No initializer
        ASSERT_EQ(varStmt.toString(), "var x;");
    }

    // Scenario 2: Declaration with integer initializer (var y = 10;)
    {
        Token varToken(TokenType::Var, "var", 2, 1);
        Token identToken(TokenType::Identifier, "y", 2, 5);
        Token intToken(TokenType::IntegerLiteral, "10", 2, 9);

        auto identifier = std::make_unique<Identifier>(identToken, "y");
        auto intLiteral = std::make_unique<IntegerLiteral>(intToken, 10);

        // Pass ownership of unique_ptrs
        VarStatement varStmt(varToken, std::move(identifier), std::move(intLiteral));

        ASSERT_EQ(varStmt.tokenLiteral(), "var");
        ASSERT_EQ(varStmt.token.type, TokenType::Var);
        ASSERT_TRUE(varStmt.name != nullptr);
        ASSERT_EQ(varStmt.name->value, "y");
        ASSERT_EQ(varStmt.name->tokenLiteral(), "y");
        ASSERT_TRUE(varStmt.value != nullptr); // Has initializer

        // Check the type and value of the initializer (optional but good)
        // Dynamic cast to check the type, or use a visitor pattern later
        IntegerLiteral* initValue = dynamic_cast<IntegerLiteral*>(varStmt.value.get());
        ASSERT_TRUE(initValue != nullptr);
        ASSERT_EQ(initValue->value, 10);
        ASSERT_EQ(initValue->tokenLiteral(), "10");

        ASSERT_EQ(varStmt.toString(), "var y = 10;");
    }
}
