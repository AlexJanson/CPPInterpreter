//
// Created by Alex on 26-9-2021.
//

#pragma once

#include "Parser.h"
#include "AST/NodeVisitor.h"

class Interpreter {
private:
    Parser parser;
    NodeVisitor* visitor;
public:
    Interpreter(Parser parser, NodeVisitor* visitor);
    ~Interpreter();
    int Interpret();
};
