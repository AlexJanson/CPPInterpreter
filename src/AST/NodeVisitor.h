//
// Created by Alex on 7-10-2021.
//

#pragma once

#include "Nodes.h"

class Visitor {
public:
    virtual void Visit(BinOp& binOpNode) = 0;
    virtual void Visit(Num& numNode) = 0;
};

class NodeVisitor : public Visitor {
public:
    int result {};
public:
    void Visit(BinOp& binOpNode) override;
    void Visit(Num& numNode) override;
};
