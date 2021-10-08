//
// Created by Alex on 7-10-2021.
//

#include "Nodes.h"
#include "NodeVisitor.h"

#include <utility>

BinOp::BinOp(std::shared_ptr<AST*> left, const Token &op, std::shared_ptr<AST*> right)
    : left(std::move(left)), op(op), token(op), right(std::move(right)) {}

void BinOp::Accept(Visitor& visitor) {
    visitor.Visit(*this);
}

Num::Num(const Token &token)
    : token(token), value(std::get<int>(token.GetValue())) {}

void Num::Accept(Visitor& visitor) {
    visitor.Visit(*this);
}

UnaryOp::UnaryOp(const Token& op, std::shared_ptr<AST*> expr)
    : op(op), token(op), expr(std::move(expr)) {}

void UnaryOp::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

void Compound::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

Program::Program(std::vector<std::shared_ptr<AST*>> children)
    : children(std::move(children)) {}

void Program::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

Compound::Compound(std::vector<std::shared_ptr<AST *>> children)
    : children(std::move(children)) {}

Assign::Assign(const std::shared_ptr<AST *> left, const Token &op, const std::shared_ptr<AST *> right)
    : op(op), token(op), left(left), right(right) {}

void Assign::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

Var::Var(const Token &token)
    : token(token), value(token.GetValue()) {}

void Var::Accept(Visitor& visitor) {
    visitor.Visit(*this);
}

void NoOp::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}
