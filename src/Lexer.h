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
        { "var", Token(Token::TokenType::VAR, "var") },
        { "float", Token(Token::TokenType::FLOAT, "float") },
        { "int", Token(Token::TokenType::INTEGER, "integer") }
    };
public:
    Lexer(std::string input);
private:
    static void Error();
    void Advance();
    void SkipWhitespace();
    void SkipComment();
    char Peek();
    Token Id();
    Token Number();
public: //TEMP
    Token GetNextToken();

    friend class Parser;
};
