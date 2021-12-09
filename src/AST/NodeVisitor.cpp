//
// Created by Alex on 7-10-2021.
//

#include "NodeVisitor.h"

#include <variant>

void NodeVisitor::Visit(BinOp &binOpNode) {
    Token::TokenType tokenType = binOpNode.op.GetType();
    binOpNode.left->Accept(*this);
    float left = result;

    binOpNode.right->Accept(*this);
    float right = result;

    switch (tokenType) {
        case Token::TokenType::PLUS: result = left + right; break;
        case Token::TokenType::MINUS: result = left - right; break;
        case Token::TokenType::MUL: result = left * right; break;
        case Token::TokenType::DIV: result = left / right; break;
        default: throw std::exception("Error");
    }
}

void NodeVisitor::Visit(Num<int>& intNode) {
    result = std::get<int>(intNode.token.GetValue());
}

void NodeVisitor::Visit(Num<float> &floatNode) {
    result = std::get<float>(floatNode.token.GetValue());
}

void NodeVisitor::Visit(UnaryOp &unaryOpNode) {
    Token::TokenType tokenType = unaryOpNode.token.GetType();
    if (tokenType == Token::TokenType::PLUS) {
        unaryOpNode.expr->Accept(*this);
        result = +result;
    }
    else if (tokenType == Token::TokenType::MINUS) {
        unaryOpNode.expr->Accept(*this);
        result = -result;
    }
}

void NodeVisitor::Visit(Module &moduleNode) {
    for (const auto& child : moduleNode.children)
        child->Accept(*this);
}

void NodeVisitor::Visit(Block &blockNode) {

}

void NodeVisitor::Visit(Compound &compoundNode) {
    for (const auto& child : compoundNode.children)
        child->Accept(*this);
}

void NodeVisitor::Visit(Assign &assignNode) {
    std::shared_ptr<Var> leftNode = std::static_pointer_cast<Var>(assignNode.left);
    std::string varName = std::get<std::string>(leftNode->value);
    assignNode.right->Accept(*this);
    globalScope.insert(std::make_pair(varName, result));
}

void NodeVisitor::Visit(Var &varNode) {
    std::string varName = std::get<std::string>(varNode.value);
    result = globalScope.count(varName) ? globalScope.at(varName) : throw std::exception("No variable with that name");
}

void NodeVisitor::Visit(VarDecl &varDeclNode) {

}

void NodeVisitor::Visit(Type &typeNode) {

}

void NodeVisitor::Visit(NoOp &noOpNode) {
}
