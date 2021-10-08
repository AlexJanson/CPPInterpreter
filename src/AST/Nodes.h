//
// Created by Alex on 7-10-2021.
//

#pragma once

#include "AST.h"
#include "../Token.h"

#include <vector>

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

class UnaryOp : public AST {
public:
    Token op, token;
    std::shared_ptr<AST*> expr;
public:
    UnaryOp(const Token& op, std::shared_ptr<AST*> expr);
    void Accept(Visitor& visitor) override;
};

class Program : public AST {
public:
    std::vector<std::shared_ptr<AST*>> children;
public:
    Program() = default;
    Program(std::vector<std::shared_ptr<AST*>> children);
    void Accept(Visitor& visitor) override;
};

class Compound : public AST {
public:
    std::vector<std::shared_ptr<AST*>> children;
public:
    Compound() = default;
    Compound(std::vector<std::shared_ptr<AST*>> children);
    void Accept(Visitor& visitor) override;
};

class Assign : public AST {
public:
    Token op, token;
    std::shared_ptr<AST*> left, right;
public:
    Assign(const std::shared_ptr<AST*> left, const Token& op, const std::shared_ptr<AST*> right);
    void Accept(Visitor& visitor) override;
};

class Var : public AST {
public:
    Token token;
    std::variant<int, std::string> value;
public:
    Var(const Token& token);
    void Accept(Visitor& visitor) override;
};

class NoOp : public AST {
public:
    NoOp() = default;
    void Accept(Visitor& visitor) override;
};