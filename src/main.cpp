#include <iostream>
#include <string>

#include "Interpreter.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
        return 0;

    auto* visitor = new NodeVisitor();
    Lexer lexer { input };
    Parser parser { lexer };
    Interpreter interpreter { parser, visitor };
    int result = interpreter.Interpret();
    std::cout << result << "\n";

    for (auto const& pair : visitor->globalScope) {
        std::cout << pair.first << ", " << pair.second << std::endl;
    }

    std::cin.get();
}
