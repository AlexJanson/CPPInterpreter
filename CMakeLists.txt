cmake_minimum_required(VERSION 3.20)
project(Custom_Interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(Custom_Interpreter src/main.cpp src/Interpreter.cpp src/Interpreter.h src/Token.cpp src/Token.h src/Lexer.cpp src/Lexer.h src/AST/AST.cpp src/AST/AST.h src/Parser.cpp src/Parser.h src/AST/NodeVisitor.cpp src/AST/NodeVisitor.h src/AST/Nodes.cpp src/AST/Nodes.h)
