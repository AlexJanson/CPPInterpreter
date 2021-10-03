//
// Created by Alex on 26-9-2021.
//

#include "Interpreter.h"

Interpreter::Interpreter(const Parser& parser)
    : parser(std::make_unique<Parser>(parser)) {}

int Interpreter::Visit_Num(const AST &node) {
    Token::TokenType tokenType = node.token.GetType();
    switch (tokenType) {
        case Token::INTEGER: return node.token.GetValue();
        default: throw std::exception("Error");
    }
}

int Interpreter::Visit_BinOp(const AST &node) {
    Token::TokenType tokenType = node.token.GetType();
    int left = Visit(node.children[0]);
    int right = Visit(node.children[1]);

    switch (tokenType) {
        case Token::PLUS: return left + right;
        case Token::MINUS: return left - right;
        case Token::MUL: return left * right;
        case Token::DIV: return left / right;
        default: throw std::exception("Error");
    }
}

int Interpreter::Visit(const AST &node) {
    Token::TokenType tokenType = node.token.GetType();
    switch (tokenType) {
        case Token::INTEGER: return Visit_Num(node);
        case Token::PLUS:
        case Token::MINUS:
        case Token::MUL:
        case Token::DIV: return Visit_BinOp(node);
        default: throw std::exception("Error");
    }
}

int Interpreter::Interpret() {
    AST tree = parser->Parse();
    return Visit(tree);
}