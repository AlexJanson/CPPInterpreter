//
// Created by Alex on 30-9-2021.
//

#pragma once

#include <vector>

#include "../Token.h"

class AST {
public:
    Token token;
    std::vector<AST> children;
};
