//
// Created by Alex on 26-9-2021.
//

#include "Token.h"

Token::Token(const Token::TokenType &type, int value)
    : type(type), value(value) {}

Token::Token(const Token::TokenType &type, float value)
    : type(type), value(value) {}

Token::Token(const Token::TokenType &type, const std::string &value)
    : type(type), value(value) {}

Token::TokenType Token::GetType() const {
    return type;
}

std::variant<int, float, std::string> Token::GetValue() const {
    return value;
}

std::string Token::GetTypeName() const {
    std::string result;
    switch (type) {
        case INTEGER:
            result = "INTEGER";
            break;
        case PLUS:
            result = "PLUS";
            break;
        case MINUS:
            result = "MINUS";
            break;
        case MUL:
            result = "MUL";
            break;
        case DIV:
            result = "DIV";
            break;
        case LPAREN:
            result = "LPAREN";
            break;
        case RPAREN:
            result = "RPAREN";
            break;
        case OPENPAREN:
            result = "OPENPAREN";
            break;
        case CLOSEPAREN:
            result = "CLOSEPAREN";
            break;
        case SEMI:
            result = "SEMI";
            break;
        case ASSIGN:
            result = "ASSIGN";
            break;
        case ID:
            result = "ID";
            break;
        case VAR:
            result = "VAR";
            break;
        case TOKENEOF:
            result = "TOKENEOF";
            break;
        default: result = "UNKNOWN";
    }

    return result;
}

std::ostream &operator<<(std::ostream& output, const Token& token) {
    if (auto value = std::get_if<std::string>(&token.value)) {
        output << "TOKEN(" << token.GetTypeName() << ", " << *value << ")";
    }
    else if (auto value = std::get_if<int>(&token.value)) {
        output << "TOKEN(" << token.GetTypeName() << ", " << *value << ")";
    }
    return output;
}
