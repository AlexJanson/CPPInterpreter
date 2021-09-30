//
// Created by Alex on 26-9-2021.
//

#pragma once
#include <iostream>

class Token {
public:
    enum TokenType {
        INTEGER = 0, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, TOKENEOF
    };
private:
    TokenType type;
    int value;
public:
    Token() = default;
    Token(const TokenType& type, int value);

    [[nodiscard]] TokenType GetType() const;
    [[nodiscard]] int GetValue() const;
private:
    friend std::ostream& operator<<(std::ostream& output, const Token& token);
};
