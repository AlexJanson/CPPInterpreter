#include <iostream>
#include <string>

#include "Interpreter.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
        return 0;

    NodeVisitor visitor;
    Lexer lexer { input };
    Parser parser { lexer };
    Interpreter interpreter { parser, visitor };
    int result = interpreter.Interpret();
    std::cout << result << "\n";

    std::cin.get();
}
