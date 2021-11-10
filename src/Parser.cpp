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

std::shared_ptr<AST *> Parser::Module() {
    std::shared_ptr<AST*> node;

    if (currentToken.GetType() == Token::OPENPAREN)
        node = CompoundStatement();
    else if (currentToken.GetType() == Token::ID)
        return std::make_shared<AST*>(new class Module(StatementList()));
    else
        node = Empty();

    return node;
}

std::vector<std::shared_ptr<AST *>> Parser::Declarations() {
    std::vector<std::shared_ptr<AST*>> declarations;

    if (currentToken.GetType() == Token::FLOAT || currentToken.GetType() == Token::INTEGER) {
        Eat(currentToken.GetType());

        while (currentToken.GetType() == Token::ID) {
            auto varDecl = VariableDeclarations();
            declarations.reserve(declarations.size() + std::distance(varDecl.begin(), varDecl.end()));
            declarations.insert(declarations.end(), varDecl.begin(), varDecl.end());
            Eat(Token::SEMI);
        }
    }

    return declarations;
}

std::vector<std::shared_ptr<AST*>> Parser::VariableDeclarations() {
    std::shared_ptr<AST*> typeNode = TypeSpec();

    std::vector<std::shared_ptr<AST*>> varNodes {
            std::make_shared<AST*>(new Var(currentToken))
    };
    Eat(Token::ID);

    while (currentToken.GetType() == Token::COMMA) {
        Eat(Token::COMMA);
        varNodes.emplace_back(std::make_shared<AST*>(new Var(currentToken)));
        Eat(Token::ID);
    }

    Eat(Token::SEMI);

    std::vector<std::shared_ptr<AST*>> varDeclarations;
    varDeclarations.reserve(varNodes.size());
    for (const auto& varNode : varNodes) {
        varDeclarations.emplace_back(std::make_shared<AST*>(new VarDecl(varNode, typeNode)));
    }

    return varDeclarations;
}

std::shared_ptr<AST*> Parser::TypeSpec() {
    Token token = currentToken;
    if (currentToken.GetType() == Token::INTEGER) {
        Eat(Token::INTEGER);
    } else {
        Eat(Token::FLOAT);
    }

    return std::make_shared<AST*>(new Type(token));
}

std::shared_ptr<AST*> Parser::CompoundStatement() {
    Eat(Token::OPENPAREN);
    std::vector<std::shared_ptr<AST*>> nodes = StatementList();
    Eat(Token::CLOSEPAREN);

    std::vector<std::shared_ptr<AST*>> children;
    children.reserve(nodes.size());
    for (const auto& node : nodes) {
        children.push_back(node);
    }

    return std::make_shared<AST*>(new Compound(children));
}

std::vector<std::shared_ptr<AST *>> Parser::StatementList() {
    auto node = Statement();

    std::vector<std::shared_ptr<AST*>> results = {node};

    while (currentToken.GetType() == Token::SEMI) {
        Eat(Token::SEMI);
        results.push_back(Statement());
    }

    if (currentToken.GetType() == Token::ID)
        Error();

    return results;
}

std::shared_ptr<AST *> Parser::Statement() {
    std::shared_ptr<AST*> node;

    if (currentToken.GetType() == Token::OPENPAREN)
        node = CompoundStatement();
    else if (currentToken.GetType() == Token::ID)
        node = AssignmentStatement();
    else
        node = Empty();

    return node;
}

std::shared_ptr<AST *> Parser::AssignmentStatement() {
    auto left = Variable();
    Token token = currentToken;
    Eat(Token::ASSIGN);
    auto right = Expr();
    auto node = std::make_shared<AST*>(new Assign(left, token, right));
    return node;
}

std::shared_ptr<AST *> Parser::Variable() {
    auto node = std::make_shared<AST*>(new Var(currentToken));
    Eat(Token::ID);
    return node;
}

std::shared_ptr<AST *> Parser::Empty() {
    return std::make_shared<AST*>(new NoOp());
}

std::shared_ptr<AST*> Parser::Factor() {
    Token token = currentToken;
    if (token.GetType() == Token::PLUS) {
        Eat(Token::PLUS);
        return std::make_shared<AST*>(new UnaryOp(token, Factor()));
    }
    else if (token.GetType() == Token::MINUS) {
        Eat(Token::MINUS);
        return std::make_shared<AST*>(new UnaryOp(token, Factor()));
    }
    else if (token.GetType() == Token::INTEGER) {
        Eat(Token::INTEGER);
        return std::make_shared<AST*>(new Num(token));
    }
    else if (token.GetType() == Token::LPAREN) {
        Eat(Token::LPAREN);
        auto node = Expr();
        Eat(Token::RPAREN);
        return node;
    }
    else {
        return Variable();
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
    auto node = Module();
    if (currentToken.GetType() != Token::TOKENEOF) {
        Error();
    }

    return node;
}
