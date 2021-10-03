//
// Created by Alex on 30-9-2021.
//

#pragma once

#include <memory>

#include "Lexer.h"
#include "AST/AST.h"

class Lexer;

class Parser {
public:
    std::shared_ptr<Lexer> lexer;
    Token currentToken;
private:
    static void Error();
    void Eat(const Token::TokenType& type);
    AST Factor();
    AST Term();
    AST Expr();
public:
    Parser(const Lexer& lexer);
    AST Parse();
};
