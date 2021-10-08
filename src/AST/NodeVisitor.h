//
// Created by Alex on 7-10-2021.
//

#pragma once

#include "Nodes.h"

#include <unordered_map>

class Visitor {
public:
    virtual void Visit(BinOp& binOpNode) = 0;
    virtual void Visit(Num& numNode) = 0;
    virtual void Visit(UnaryOp& unaryOpNode) = 0;
    virtual void Visit(Program& programNode) = 0;
    virtual void Visit(Compound& compoundNode) = 0;
    virtual void Visit(Assign& assignNode) = 0;
    virtual void Visit(Var& varNode) = 0;
    virtual void Visit(NoOp& noOpNode) = 0;
};

class NodeVisitor : public Visitor {
public:
    int result {};
    std::unordered_map<std::string, int> globalScope; // TEMP HACK
public:
    void Visit(BinOp& binOpNode) override;
    void Visit(Num& numNode) override;
    void Visit(UnaryOp& unaryOpNode) override;
    void Visit(Program& programNode) override;
    void Visit(Compound& compoundNode) override;
    void Visit(Assign& assignNode) override;
    void Visit(Var& varNode) override;
    void Visit(NoOp& noOpNode) override;
};
