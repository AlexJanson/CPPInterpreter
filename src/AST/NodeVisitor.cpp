//
// Created by Alex on 7-10-2021.
//

#include "NodeVisitor.h"

#include <variant>

void NodeVisitor::Visit(BinOp &binOpNode) {
    Token::TokenType tokenType = binOpNode.op.GetType();
    (*binOpNode.left)->Accept(*this);
    int left = result;

    (*binOpNode.right)->Accept(*this);
    int right = result;

    switch (tokenType) {
        case Token::PLUS: result = left + right; break;
        case Token::MINUS: result = left - right; break;
        case Token::MUL: result = left * right; break;
        case Token::DIV: result = left / right; break;
        default: throw std::exception("Error");
    }
}

void NodeVisitor::Visit(Num &numNode) {
    Token::TokenType tokenType = numNode.token.GetType();
    switch (tokenType) {
        case Token::INTEGER: result = std::get<int>(numNode.token.GetValue()); break;
        default: throw std::exception("Error");
    }
}

void NodeVisitor::Visit(UnaryOp &unaryOpNode) {
    Token::TokenType tokenType = unaryOpNode.token.GetType();
    if (tokenType == Token::PLUS) {
        (*unaryOpNode.expr)->Accept(*this);
        result = +result;
    }
    else if (tokenType == Token::MINUS) {
        (*unaryOpNode.expr)->Accept(*this);
        result = -result;
    }
}

void NodeVisitor::Visit(Program &programNode) {
    for (const auto& child : programNode.children)
        (*child)->Accept(*this);
}

void NodeVisitor::Visit(Compound &compoundNode) {
    for (const auto& child : compoundNode.children)
        (*child)->Accept(*this);
}

void NodeVisitor::Visit(Assign &assignNode) {
    Var* leftNode = (Var*)(*assignNode.left);
    std::string varName = std::get<std::string>(leftNode->value);
    (*assignNode.right)->Accept(*this);
    globalScope.insert(std::make_pair(varName, result));
}

void NodeVisitor::Visit(Var &varNode) {
    std::string varName = std::get<std::string>(varNode.value);
    result = globalScope.count(varName) ? globalScope.at(varName) : throw std::exception("No variable with that name");
}

void NodeVisitor::Visit(NoOp &noOpNode) {
}
