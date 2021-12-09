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
    std::shared_ptr<AST> left, right;
public:
    BinOp(std::shared_ptr<AST> left, const Token& op, std::shared_ptr<AST> right);
    void Accept(Visitor& visitor) override;
};

template<typename T>
class Num : public AST {
public:
    Token token;
    T value;
public:
    Num(const Token& token);
    void Accept(Visitor& visitor) override;
};

class UnaryOp : public AST {
public:
    Token op, token;
    std::shared_ptr<AST> expr;
public:
    UnaryOp(const Token& op, std::shared_ptr<AST> expr);
    void Accept(Visitor& visitor) override;
};

class Module : public AST {
public:
    std::vector<std::shared_ptr<AST>> children;
public:
    Module() = default;
    Module(std::vector<std::shared_ptr<AST>> children);
    void Accept(Visitor& visitor) override;
};

class Block : public AST {
public:
    std::vector<std::shared_ptr<AST*>> declarations;
    std::vector<std::shared_ptr<AST*>> compoundStatements;
public:
    Block(std::vector<std::shared_ptr<AST*>> declarations, std::vector<std::shared_ptr<AST*>> compoundStatements);
    void Accept(Visitor& visitor) override;
};

class Compound : public AST {
public:
    std::vector<std::shared_ptr<AST>> children;
public:
    Compound() = default;
    Compound(std::vector<std::shared_ptr<AST>> children);
    void Accept(Visitor& visitor) override;
};

class Assign : public AST {
public:
    Token op, token;
    std::shared_ptr<AST> left, right;
public:
    Assign(std::shared_ptr<AST> left, const Token& op, std::shared_ptr<AST> right);
    void Accept(Visitor& visitor) override;
};

class Var : public AST {
public:
    Token token;
    std::variant<int, float, std::string> value;
public:
    Var(const Token& token);
    void Accept(Visitor& visitor) override;
};

class VarDecl : public AST {
public:
    std::shared_ptr<AST> varNode;
    std::shared_ptr<AST> typeNode;
public:
    VarDecl(std::shared_ptr<AST> varNode, std::shared_ptr<AST> typeNode);
    void Accept(Visitor& visitor) override;
};

class Type : public AST {
public:
    Token token;
    std::variant<int, float, std::string> value;
public:
    Type(const Token& token);
    void Accept(Visitor& visitor) override;
};

class NoOp : public AST {
public:
    NoOp() = default;
    void Accept(Visitor& visitor) override;
};