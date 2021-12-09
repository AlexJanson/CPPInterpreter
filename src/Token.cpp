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
        case TokenType::INTEGER:
            result = "INTEGER";
            break;
        case TokenType::PLUS:
            result = "PLUS";
            break;
        case TokenType::MINUS:
            result = "MINUS";
            break;
        case TokenType::MUL:
            result = "MUL";
            break;
        case TokenType::DIV:
            result = "DIV";
            break;
        case TokenType::LPAREN:
            result = "LPAREN";
            break;
        case TokenType::RPAREN:
            result = "RPAREN";
            break;
        case TokenType::OPENPAREN:
            result = "OPENPAREN";
            break;
        case TokenType::CLOSEPAREN:
            result = "CLOSEPAREN";
            break;
        case TokenType::SEMI:
            result = "SEMI";
            break;
        case TokenType::ASSIGN:
            result = "ASSIGN";
            break;
        case TokenType::ID:
            result = "ID";
            break;
        case TokenType::VAR:
            result = "VAR";
            break;
        case TokenType::TOKENEOF:
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
