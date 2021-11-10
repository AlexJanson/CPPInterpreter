//
// Created by Alex on 10-11-2021.
//

#include <gtest/gtest.h>
#include <Utils/File.h>
#include <Interpreter.h>

TEST(HelloTest, BasicAssertions) {
    File file("C:/CLion Projects/CPPInterpreter/src/file.txt");
    std::string input = file.GetFileContentsAsString();

    auto* visitor = new NodeVisitor();
    Lexer lexer { input };
    Parser parser { lexer };
    Interpreter interpreter { parser, visitor };
    int result = interpreter.Interpret();
    std::cout << result << "\n";

    EXPECT_EQ(result, 8);
}