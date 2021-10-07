//
// Created by Alex on 26-9-2021.
//

#pragma once

#include "Parser.h"
#include "AST/NodeVisitor.h"

#include <memory>

class Interpreter {
private:
    std::unique_ptr<Parser> parser;
    std::unique_ptr<NodeVisitor> visitor;
public:
    Interpreter(const Parser& parser, const NodeVisitor& visitor);
    int Interpret();
};
