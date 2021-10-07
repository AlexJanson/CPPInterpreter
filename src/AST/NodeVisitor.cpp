//
// Created by Alex on 7-10-2021.
//

#include "NodeVisitor.h"

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
        case Token::INTEGER: result = numNode.token.GetValue(); break;
        default: throw std::exception("Error");
    }
}
