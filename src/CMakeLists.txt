cmake_minimum_required(VERSION 3.20)

project(Interpreter)

add_library(Interpreter_lib STATIC Interpreter.cpp Interpreter.h Token.cpp Token.h Lexer.cpp Lexer.h AST/AST.cpp AST/AST.h Parser.cpp Parser.h AST/NodeVisitor.cpp AST/NodeVisitor.h AST/Nodes.cpp AST/Nodes.h Utils/File.cpp Utils/File.h)
