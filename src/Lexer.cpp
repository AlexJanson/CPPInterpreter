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

void Lexer::SkipComment() {
    while (currentChar != '*' && Peek() != '/') {
        Advance();
    }

    Advance();
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

    Token token = reservedKeywords.count(result) ? reservedKeywords.at(result) : Token(Token::TokenType::ID, result);
    return token;
}

Token Lexer::Number() {
    std::string result;
    while (isdigit(currentChar)) {
        result += currentChar;
        Advance();
    }

    if (currentChar == '.') {
        result += currentChar;
        Advance();

        while (isdigit(currentChar)) {
            result += currentChar;
            Advance();
        }

        return {Token::TokenType::FLOAT_CONST, std::stof(result)};
    }

    return {Token::TokenType::INTEGER_CONST, std::stoi(result)};
}

Token Lexer::GetNextToken() {
    while (currentChar) {
        if (isspace(currentChar)) {
            SkipWhitespace();
            continue;
        }

        if (currentChar == '/' && Peek() == '*') {
            Advance();
            Advance();
            SkipComment();
            continue;
        }

        if (isalpha(currentChar))
            return Id();

        if (isdigit(currentChar))
            return Number();

        if (currentChar == '+') {
            Advance();
            return {Token::TokenType::PLUS, "+"};
        }

        if (currentChar == '-') {
            Advance();
            return {Token::TokenType::MINUS, "-"};
        }

        if (currentChar == '*') {
            Advance();
            return {Token::TokenType::MUL, "*"};
        }

        if (currentChar == '/') {
            Advance();
            return {Token::TokenType::DIV, "/"};
        }

        if (currentChar == '(') {
            Advance();
            return {Token::TokenType::LPAREN, "("};
        }

        if (currentChar == ')') {
            Advance();
            return {Token::TokenType::RPAREN, ")"};
        }

        if (currentChar == '{') {
            Advance();
            return {Token::TokenType::OPENPAREN, "{"};
        }

        if (currentChar == '}') {
            Advance();
            return {Token::TokenType::CLOSEPAREN, "}"};
        }

        if (currentChar == '=') {
            Advance();
            return {Token::TokenType::ASSIGN, "="};
        }

        if (currentChar == ';') {
            Advance();
            return {Token::TokenType::SEMI, ";"};
        }

        if (currentChar == ',') {
            Advance();
            return {Token::TokenType::COMMA, ","};
        }

        Error();
    }

    return {Token::TokenType::TOKENEOF, 0};
}

Lexer::Lexer(std::string input)
    : text(std::move(input)), pos(0), currentChar(text[pos]) {}
