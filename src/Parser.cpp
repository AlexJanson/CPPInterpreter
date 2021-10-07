//
// Created by Alex on 30-9-2021.
//

#include "Parser.h"
#include "AST/Nodes.h"

Parser::Parser(const Lexer &lexer)
    : lexer(std::make_unique<Lexer>(lexer)), currentToken(this->lexer->GetNextToken()) {}

void Parser::Error() {
    throw std::exception("Error parsing input");
}

void Parser::Eat(const Token::TokenType& type) {
    if (currentToken.GetType() == type)
        currentToken = lexer->GetNextToken();
    else
        Error();
}

std::shared_ptr<AST*> Parser::Factor() {
    Token token = currentToken;
    if (token.GetType() == Token::INTEGER) {
        Eat(Token::INTEGER);
        return std::make_shared<AST*>(new Num(token));
    }
    else if (token.GetType() == Token::LPAREN) {
        Eat(Token::LPAREN);
        auto node = Expr();
        Eat(Token::RPAREN);
        return node;
    }
}

std::shared_ptr<AST*> Parser::Term() {
    auto node = Factor();

    while (currentToken.GetType() == Token::MUL || currentToken.GetType() == Token::DIV) {
        Token token = currentToken;
        if (currentToken.GetType() == Token::MUL)
            Eat(Token::MUL);
        else if (currentToken.GetType() == Token::DIV)
            Eat(Token::DIV);
        else
            throw std::exception("Invalid syntax");

        node = std::make_shared<AST*>(new BinOp(node, token, Factor()));
    }

    return node;
}

std::shared_ptr<AST*> Parser::Expr() {
    auto node = Term();

    while (currentToken.GetType() == Token::PLUS || currentToken.GetType() == Token::MINUS) {
        Token token = currentToken;
        if (token.GetType() == Token::PLUS)
            Eat(Token::PLUS);
        else if (token.GetType() == Token::MINUS)
            Eat(Token::MINUS);
        else
            throw std::exception("Invalid syntax");

        node = std::make_shared<AST*>(new BinOp(node, token, Term()));
    }

    return node;
}

std::shared_ptr<AST*> Parser::Parse() {
    return Expr();
}
