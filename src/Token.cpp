//
// Created by Alex on 26-9-2021.
//

#include "Token.h"

Token::Token(const Token::TokenType &type, int value)
    : type(type), value(value) {}

std::ostream &operator<<(std::ostream& output, const Token& token) {
    output << token.value;
    return output;
}

Token::TokenType Token::GetType() const {
    return type;
}

int Token::GetValue() const {
    return value;
}


