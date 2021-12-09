//
// Created by Alex on 4-11-2021.
//

#include "File.h"

#include <utility>

File::File(std::string filepath)
    : filepath(std::move(filepath)) {
    std::ifstream file(this->filepath);
    if (file.is_open() && file.good())
        buffer << file.rdbuf();
    else
        throw std::exception("Could not open file");
}

std::string File::GetFileContentsAsString() {
    return buffer.str();
}
