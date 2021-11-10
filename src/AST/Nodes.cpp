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

Module::Module(std::vector<std::shared_ptr<AST*>> children)
    : children(std::move(children)) {}

void Module::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

Block::Block(std::vector<std::shared_ptr<AST *>> declarations, std::vector<std::shared_ptr<AST *>> compoundStatements)
    : declarations(std::move(declarations)), compoundStatements(std::move(compoundStatements)) {}

void Block::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

Compound::Compound(std::vector<std::shared_ptr<AST *>> children)
    : children(std::move(children)) {}

Assign::Assign(std::shared_ptr<AST*> left, const Token& op, std::shared_ptr<AST*> right)
    : op(op), token(op), left(std::move(left)), right(std::move(right)) {}

void Assign::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

Var::Var(const Token &token)
    : token(token), value(token.GetValue()) {}

void Var::Accept(Visitor& visitor) {
    visitor.Visit(*this);
}

VarDecl::VarDecl(std::shared_ptr<AST *> varNode, std::shared_ptr<AST *> typeNode)
        : varNode(std::move(varNode)), typeNode(std::move(typeNode)) {}

void VarDecl::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

Type::Type(const Token& token)
    : token(token), value(token.GetValue()) {}

void Type::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}

void NoOp::Accept(Visitor &visitor) {
    visitor.Visit(*this);
}
