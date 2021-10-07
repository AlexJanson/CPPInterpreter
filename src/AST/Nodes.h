//
// Created by Alex on 7-10-2021.
//

#pragma once

#include "AST.h"
#include "../Token.h"

class BinOp : public AST {
public:
    Token op, token;
    std::shared_ptr<AST*> left, right;
public:
    BinOp(std::shared_ptr<AST*> left, const Token& op, std::shared_ptr<AST*> right);
    void Accept(Visitor& visitor) override;
};

class Num : public AST {
public:
    Token token;
    int value;
public:
    Num(const Token& token);
    void Accept(Visitor& visitor) override;
};
