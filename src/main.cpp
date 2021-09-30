#include <iostream>
#include <string>

#include "Interpreter.h"
#include "Lexer.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
        return 0;

    Lexer lexer { input };
    Interpreter interpreter { lexer };
    int result = interpreter.Expr();
    std::cout << result << "\n";

    std::cin.get();
}
