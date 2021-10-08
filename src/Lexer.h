//
// Created by Alex on 27-9-2021.
//

#pragma once

#include "Token.h"
#include "Parser.h"

#include <unordered_map>

class Lexer {
private:
    std::string text;
    int pos = 0;
    char currentChar;

    std::unordered_map<std::string, Token> reservedKeywords = {
            { "var", Token(Token::VAR, "var") }
    };
public:
    Lexer(std::string input);
private:
    static void Error();
    void Advance();
    void SkipWhitespace();
    char Peek();
    Token Id();
    int Integer();
public: //TEMP
    Token GetNextToken();

    friend class Parser;
};
