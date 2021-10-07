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
    std::shared_ptr<AST*> Factor();
    std::shared_ptr<AST*> Term();
    std::shared_ptr<AST*> Expr();
public:
    Parser(const Lexer& lexer);
    std::shared_ptr<AST*> Parse();
};
