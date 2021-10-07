//
// Created by Alex on 30-9-2021.
//

#pragma once

class Visitor;

class AST {
public:
    virtual ~AST() = default;
    virtual void Accept(Visitor& visitor) = 0;
};
