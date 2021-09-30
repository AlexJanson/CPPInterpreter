//
// Created by Alex on 27-9-2021.
//

#include "Lexer.h"
#include <string>

void Lexer::Error() {
    throw std::exception("Invalid character");
}

void Lexer::Advance() {
    pos += 1;
    if (pos > text.length() - 1)
        currentChar = 0;
    else
        currentChar = text[pos];
}

void Lexer::SkipWhitespace() {
    while (isspace(currentChar))
        Advance();
}

int Lexer::Integer() {
    std::string result;
    while (isdigit(currentChar)) {
        result += currentChar;
        Advance();
    }

    return std::stoi(result);
}

Token Lexer::GetNextToken() {
    while (currentChar) {
        if (isspace(currentChar)) {
            SkipWhitespace();
            continue;
        }

        if (isdigit(currentChar))
            return {Token::INTEGER, Integer()};

        if (currentChar == '+') {
            Advance();
            return {Token::PLUS, '+'};
        }

        if (currentChar == '-') {
            Advance();
            return {Token::MINUS, '-'};
        }

        if (currentChar == '*') {
            Advance();
            return {Token::MUL, '*'};
        }

        if (currentChar == '/') {
            Advance();
            return {Token::DIV, '/'};
        }

        if (currentChar == '(') {
            Advance();
            return {Token::LPAREN, '('};
        }

        if (currentChar == ')') {
            Advance();
            return {Token::RPAREN, ')'};
        }

        Error();
    }

    return {Token::TOKENEOF, 0};
}

Lexer::Lexer(std::string input)
    : text(std::move(input)), pos(0), currentChar(text[pos]) {}
