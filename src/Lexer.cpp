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

char Lexer::Peek() {
    int peekPos = pos + 1;
    if (peekPos > text.length() - 1)
        return -1;
    return text[peekPos];
}

Token Lexer::Id() {
    std::string result;
    while (currentChar && isalnum(currentChar)) {
        result += currentChar;
        Advance();
    }

    Token token = reservedKeywords.count(result) ? reservedKeywords.at(result) : Token(Token::ID, result);
    return token;
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

        if (isalpha(currentChar))
            return Id();

        if (isdigit(currentChar))
            return {Token::INTEGER, Integer()};

        if (currentChar == '+') {
            Advance();
            return {Token::PLUS, "+"};
        }

        if (currentChar == '-') {
            Advance();
            return {Token::MINUS, "-"};
        }

        if (currentChar == '*') {
            Advance();
            return {Token::MUL, "*"};
        }

        if (currentChar == '/') {
            Advance();
            return {Token::DIV, "/"};
        }

        if (currentChar == '(') {
            Advance();
            return {Token::LPAREN, "("};
        }

        if (currentChar == ')') {
            Advance();
            return {Token::RPAREN, ")"};
        }

        if (currentChar == '{') {
            Advance();
            return {Token::OPENPAREN, "{"};
        }

        if (currentChar == '}') {
            Advance();
            return {Token::CLOSEPAREN, "}"};
        }

        if (currentChar == '=') {
            Advance();
            return {Token::ASSIGN, "="};
        }

        if (currentChar == ';') {
            Advance();
            return {Token::SEMI, ";"};
        }

        Error();
    }

    return {Token::TOKENEOF, 0};
}

Lexer::Lexer(std::string input)
    : text(std::move(input)), pos(0), currentChar(text[pos]) {}
