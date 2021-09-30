//
// Created by Alex on 26-9-2021.
//

#pragma once

#include "Parser.h"

#include <memory>

class Interpreter {
private:
    std::unique_ptr<Parser> parser;
public:
    Interpreter(const Parser& parser);
    int Visit();
    int Interpret();
};
