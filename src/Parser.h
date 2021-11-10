//
// Created by Alex on 30-9-2021.
//

#pragma once

#include <memory>

#include "Lexer.h"
#include "AST/AST.h"

#include <vector>

class Lexer;

class Parser {
public:
    std::shared_ptr<Lexer> lexer;
    Token currentToken;
private:
    static void Error();
    void Eat(const Token::TokenType& type);
    std::shared_ptr<AST*> Module();
    std::shared_ptr<AST*> Block();
    std::vector<std::shared_ptr<AST*>> Declarations();
    std::vector<std::shared_ptr<AST*>> VariableDeclarations();
    std::shared_ptr<AST*> TypeSpec();
    std::shared_ptr<AST*> CompoundStatement();
    std::vector<std::shared_ptr<AST *>> StatementList();
    std::shared_ptr<AST*> Statement();
    std::shared_ptr<AST*> AssignmentStatement();
    std::shared_ptr<AST*> Variable();
    std::shared_ptr<AST*> Empty();
    std::shared_ptr<AST*> Factor();
    std::shared_ptr<AST*> Term();
    std::shared_ptr<AST*> Expr();
public:
    Parser(const Lexer& lexer);
    std::shared_ptr<AST*> Parse();
};
