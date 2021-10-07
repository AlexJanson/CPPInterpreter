//
// Created by Alex on 26-9-2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(const Parser& parser, const NodeVisitor& visitor)
    : parser(std::make_unique<Parser>(parser)), visitor(std::make_unique<NodeVisitor>(visitor)) {}

int Interpreter::Interpret() {
    std::shared_ptr<AST*> tree = parser->Parse();
    (*tree)->Accept((*visitor));
    return visitor->result;
}