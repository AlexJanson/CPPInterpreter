//
// Created by Alex on 10-11-2021.
//

#include <gtest/gtest.h>
#include <Utils/File.h>
#include <Interpreter.h>

class ProgramTest : public ::testing::Test {
protected:
    Lexer lexer{""};
    Parser parser{lexer};
    Interpreter interpreter{parser, nullptr};

    ProgramTest() {};

    void SetUp() override {
        lexer = { "" };
        parser = { lexer };
        interpreter = { parser, nullptr };
    }

    void TearDown() override {

    };
};

TEST_F(ProgramTest, BasicAssertions) {
    File file("D:/CLion Projects/CPPInterpreter/src/file.txt");
    std::string input = file.GetFileContentsAsString();

    auto* visitor = new NodeVisitor();
    Lexer lexer { input };
    Parser parser { lexer };
    Interpreter interpreter { parser, visitor };
    float result = interpreter.Interpret();
    std::cout << result << "\n";

    EXPECT_EQ(result, 7.2f);
}