//
// Created by Alex on 27-9-2021.
//

#pragma once

#include "Token.h"
#include "Parser.h"

class Lexer {
private:
    std::string text;
    int pos = 0;
    char currentChar;
public:
    Lexer(std::string input);
private:
    static void Error();
    void Advance();
    void SkipWhitespace();
    int Integer();
    Token GetNextToken();

    friend class Parser;
};
