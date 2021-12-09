//
// Created by Alex on 4-11-2021.
//

#pragma once

#include <string>
#include <fstream>
#include <sstream>

class File {
private:
    std::string filepath;
    std::stringstream buffer;
public:
    File(std::string filepath);

    std::string GetFileContentsAsString();
};

