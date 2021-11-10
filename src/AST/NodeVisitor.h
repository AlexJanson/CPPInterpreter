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
    virtual void Visit(Module& moduleNode) = 0;
    virtual void Visit(Block& blockNode) = 0;
    virtual void Visit(Compound& compoundNode) = 0;
    virtual void Visit(Assign& assignNode) = 0;
    virtual void Visit(Var& varNode) = 0;
    virtual void Visit(VarDecl& varDeclNode) = 0;
    virtual void Visit(Type& typeNode) = 0;
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
    void Visit(Module& moduleNode) override;
    void Visit(Block& blockNode) override;
    void Visit(Compound& compoundNode) override;
    void Visit(Assign& assignNode) override;
    void Visit(Var& varNode) override;
    void Visit(VarDecl& varDeclNode) override;
    void Visit(Type& typeNode) override;
    void Visit(NoOp& noOpNode) override;
};
