//
// Created by Alex on 26-9-2021.
//

#include "Interpreter.h"

#include <utility>

Interpreter::Interpreter(Parser parser, NodeVisitor* visitor)
    : parser(std::move(parser)), visitor(visitor) {}

Interpreter::~Interpreter() {
    delete visitor;
}

int Interpreter::Interpret() {
    std::shared_ptr<AST*> tree = parser.Parse();
    (*tree)->Accept(*visitor);
    return visitor->result;
}

