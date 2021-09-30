//
// Created by Alex on 30-9-2021.
//

#pragma once

#include "AST.h"
#include "../Token.h"

class BinOp : public AST
{
public:
    Token token;
    Token op;
    AST left;
    AST right;
public:
    BinOp(AST left, Token op, AST right)
        : token(op), op(op), left(left), right(right) {}
};

class Num : public AST
{
public:
    Token token;
    int value;
public:
    Num(Token token)
        : token(token), value(token.GetValue()) {}
};