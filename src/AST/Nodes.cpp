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
    : token(token), value(token.GetValue()) {}

void Num::Accept(Visitor& visitor) {
    visitor.Visit(*this);
}
