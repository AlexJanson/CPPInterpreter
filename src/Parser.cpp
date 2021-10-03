//
// Created by Alex on 30-9-2021.
//

#include "Parser.h"

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

AST Parser::Factor() {
    Token token = currentToken;
    if (token.GetType() == Token::INTEGER) {
        Eat(Token::INTEGER);
        return {token, {}};
    }
    else if (token.GetType() == Token::LPAREN) {
        Eat(Token::LPAREN);
        AST node = Expr();
        Eat(Token::RPAREN);
        return node;
    }
}

AST Parser::Term() {
    AST node = Factor();

    while (currentToken.GetType() == Token::MUL || currentToken.GetType() == Token::DIV) {
        Token token = currentToken;
        if (currentToken.GetType() == Token::MUL) {
            Eat(Token::MUL);
            std::vector<AST> children = {node, Factor()};
            node = {token, children};
        }
        else if (currentToken.GetType() == Token::DIV) {
            Eat(Token::DIV);
            std::vector<AST> children = {node, Factor()};
            node = {token, children};
        }
        else {
            throw std::exception("Invalid syntax");
        }
    }

    return node;
}

AST Parser::Expr() {
    AST node = Term();

    while (currentToken.GetType() == Token::PLUS || currentToken.GetType() == Token::MINUS) {
        Token token = currentToken;
        if (token.GetType() == Token::PLUS) {
            Eat(Token::PLUS);
            std::vector<AST> children = {node, Term()};
            return {token, children};
        }
        else if (token.GetType() == Token::MINUS) {
            Eat(Token::MINUS);
            std::vector<AST> children = {node, Term()};
            return {token, children};
        }
        else {
            throw std::exception("Invalid syntax");
        }

    }

    return node;
}

AST Parser::Parse() {
    return Expr();
}
