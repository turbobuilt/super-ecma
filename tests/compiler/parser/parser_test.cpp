#include "compiler/parser/parser.h" // Include the Parser header
#include "compiler/lexer/lexer.h"
#include "compiler/ast/program.h" // Include Program AST node
#include "compiler/ast/statement.h" // Include Statement AST nodes (like VarStatement)
#include "compiler/ast/expression.h" // Include Expression AST nodes (like Identifier)
#include "test_runner.h"

#include <string>
#include <vector>
#include <memory> // For unique_ptr

// Helper function to check for parser errors
void checkParserErrors(const Parser& parser) {
    const auto& errors = parser.getErrors();
    if (errors.empty()) {
        return;
    }

    std::cerr << "Parser encountered " << errors.size() << " errors:" << std::endl;
    for (const auto& msg : errors) {
        std::cerr << "  Parser error: " << msg << std::endl;
    }
    // Use ASSERT_TRUE(false) to fail the test if errors are found
    ASSERT_TRUE(errors.empty());
}


// Test case for basic parser initialization and error checking
TEST_CASE(TestParserInitialization) {
    std::string input = "var x = 5;";
    Lexer lexer(input);
    Parser parser(lexer);

    // Check that initially there are no errors (or handle expected init errors)
    checkParserErrors(parser);

    // Attempt to parse the program
    auto program = parser.parseProgram();

    // Check for errors *after* parsing
    checkParserErrors(parser);

    // Basic check that program is not null
    ASSERT_TRUE(program != nullptr);

    // Add more specific checks about the parsed program structure later
    // ASSERT_EQ(program->statements.size(), 1);
}

// Add more test cases for parsing specific statements (Var, Return, etc.)

// Test case for parsing a string literal expression
TEST_CASE(TestParseStringLiteralExpression) {
    std::string input = "\"hello world\";"; // Note: Escaped quotes for C++ string literal
    Lexer lexer(input);
    Parser parser(lexer);
    auto program = parser.parseProgram();
    checkParserErrors(parser);

    ASSERT_TRUE(program != nullptr);
    ASSERT_EQ(program->statements.size(), 1);

    // Check the statement type
    Statement* stmt = program->statements[0].get();
    ASSERT_TRUE(stmt != nullptr);
    ExpressionStatement* exprStmt = dynamic_cast<ExpressionStatement*>(stmt);
    ASSERT_TRUE(exprStmt != nullptr);

    // Check the expression type
    Expression* expr = exprStmt->expression.get();
    ASSERT_TRUE(expr != nullptr);
    StringLiteral* strLiteral = dynamic_cast<StringLiteral*>(expr);
    ASSERT_TRUE(strLiteral != nullptr);

    // Check the value of the string literal
    ASSERT_EQ(strLiteral->value, "hello world"); // AST value should not have quotes
    ASSERT_EQ(strLiteral->tokenLiteral(), "\"hello world\""); // Token literal includes quotes
}

/*
TEST_CASE(TestParseVarStatement) {
    std::string input = R"(
        var x = 5;
        var y = 10;
        var foobar = 838383;
    )";
    Lexer lexer(input);
    Parser parser(lexer);
    auto program = parser.parseProgram();
    checkParserErrors(parser);

    ASSERT_TRUE(program != nullptr);
    ASSERT_EQ(program->statements.size(), 3);

    std::vector<std::string> expectedIdentifiers = {"x", "y", "foobar"};

    for (size_t i = 0; i < expectedIdentifiers.size(); ++i) {
        Statement* stmt = program->statements[i].get();
        ASSERT_TRUE(stmt != nullptr);
        // Add type check for VarStatement (e.g., using dynamic_cast or visitor)
        VarStatement* varStmt = dynamic_cast<VarStatement*>(stmt);
        ASSERT_TRUE(varStmt != nullptr);
        ASSERT_EQ(varStmt->tokenLiteral(), "var");
        ASSERT_TRUE(varStmt->name != nullptr);
        ASSERT_EQ(varStmt->name->value, expectedIdentifiers[i]);
        ASSERT_EQ(varStmt->name->tokenLiteral(), expectedIdentifiers[i]);
        // Add checks for the value later
    }
}
*/
