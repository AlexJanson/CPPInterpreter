//
// Created by Alex on 26-9-2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(const Parser& parser)
    : parser(std::make_unique<Parser>(parser)) {}
