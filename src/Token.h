//
// Created by Alex on 26-9-2021.
//

#pragma once
#include <iostream>
#include <variant>

class Token {
public:
    enum TokenType {
        INTEGER = 0, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, OPENPAREN, CLOSEPAREN, SEMI, ASSIGN, ID, VAR, TOKENEOF
    };
private:
    TokenType type;
    std::variant<int, std::string> value;
public:
    Token() = default;
    Token(const TokenType& type, int value);
    Token(const TokenType& type, const std::string& value);

    [[nodiscard]] TokenType GetType() const;
    [[nodiscard]] std::variant<int, std::string> GetValue() const;

    std::string GetTypeName() const;
private:
    friend std::ostream& operator<<(std::ostream& output, const Token& token);
};
