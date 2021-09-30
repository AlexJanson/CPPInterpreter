//
// Created by Alex on 30-9-2021.
//

#include "Parser.h"
#include "./AST/Nodes.h"

Parser::Parser(const Lexer &lexer)
    : lexer(std::make_unique<Lexer>(lexer)) {}

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
        return Num(token);
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
        if (token.GetType() == Token::MUL) {
            Eat(Token::MUL);
        }
        else if (token.GetType() == Token::DIV) {
            Eat(Token::DIV);
        }

        node = BinOp(node, token, Factor());

    }
    return node;
}

AST Parser::Expr() {
    AST node = Term();

    while (currentToken.GetType() == Token::PLUS || currentToken.GetType() == Token::MINUS) {
        Token token = currentToken;
        if (token.GetType() == Token::PLUS) {
            Eat(Token::PLUS);
        }
        else if (token.GetType() == Token::MINUS) {
            Eat(Token::MINUS);
        }

        node = BinOp(node, token, Term());
    }

    return node;
}

AST Parser::Parse() {
    return Expr();
}
