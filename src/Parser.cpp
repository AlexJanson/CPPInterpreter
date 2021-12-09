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

std::shared_ptr<AST> Parser::Module() {
    std::shared_ptr<AST> node;

    Declarations();

    if (currentToken.GetType() == Token::TokenType::OPENPAREN)
        node = CompoundStatement();
    else if (currentToken.GetType() == Token::TokenType::ID)
        return std::make_shared<class Module>(class Module(StatementList()));
    else
        node = Empty();

    return node;
}

std::vector<std::shared_ptr<AST>> Parser::Declarations() {
    std::vector<std::shared_ptr<AST>> declarations;

    // 1. get the type of the variable(s)
    // 2. loop over all the IDs
    // 3. Eat the SEMI
    // 4. repeat

    // maybe:
    // while current is FLOAT or INTEGER repeat ^?

    while (currentToken.GetType() == Token::TokenType::FLOAT || currentToken.GetType() == Token::TokenType::INTEGER) {
        std::shared_ptr<AST> typeNode = TypeSpec();

        if (currentToken.GetType() == Token::TokenType::ID) {
            auto varDecl = VariableDeclarations(typeNode);
            declarations.reserve(declarations.size() + std::distance(varDecl.begin(), varDecl.end()));
            declarations.insert(declarations.end(), varDecl.begin(), varDecl.end());
            Eat(Token::TokenType::SEMI);
        }
    }

    return declarations;
}

std::vector<std::shared_ptr<AST>> Parser::VariableDeclarations(std::shared_ptr<AST> typeNode) {

    // VAR holds the name and call Expr() for the value?
    // make a VarDecl that has both the name and the value and type?

    std::vector<std::shared_ptr<AST>> varNodes {
            std::make_shared<Var>(currentToken)
    };
    Eat(Token::TokenType::ID);

    while (currentToken.GetType() == Token::TokenType::COMMA) {
        Eat(Token::TokenType::COMMA);
        varNodes.emplace_back(std::make_shared<Var>(currentToken));
        Eat(Token::TokenType::ID);
    }

    Eat(Token::TokenType::SEMI);

    std::vector<std::shared_ptr<AST>> varDeclarations;
    varDeclarations.reserve(varNodes.size());
    for (const auto& varNode : varNodes) {
        varDeclarations.emplace_back(std::make_shared<VarDecl>(varNode, typeNode));
    }

    return varDeclarations;
}

std::shared_ptr<AST> Parser::TypeSpec() {
    Token token = currentToken;
    if (currentToken.GetType() == Token::TokenType::INTEGER) {
        Eat(Token::TokenType::INTEGER);
    } else {
        Eat(Token::TokenType::FLOAT);
    }

    return std::make_shared<Type>(token);
}

std::shared_ptr<AST> Parser::CompoundStatement() {
    Eat(Token::TokenType::OPENPAREN);
    std::vector<std::shared_ptr<AST>> nodes = StatementList();
    Eat(Token::TokenType::CLOSEPAREN);

    std::vector<std::shared_ptr<AST>> children;
    children.reserve(nodes.size());
    for (const auto& node : nodes) {
        children.push_back(node);
    }

    return std::make_shared<Compound>(children);
}

std::vector<std::shared_ptr<AST>> Parser::StatementList() {
    auto node = Statement();

    std::vector<std::shared_ptr<AST>> results = {node};

    while (currentToken.GetType() == Token::TokenType::SEMI) {
        Eat(Token::TokenType::SEMI);
        results.push_back(Statement());
    }

    if (currentToken.GetType() == Token::TokenType::ID)
        Error();

    return results;
}

std::shared_ptr<AST> Parser::Statement() {
    std::shared_ptr<AST> node;

    if (currentToken.GetType() == Token::TokenType::OPENPAREN)
        node = CompoundStatement();
    else if (currentToken.GetType() == Token::TokenType::ID)
        node = AssignmentStatement();
    else
        node = Empty();

    return node;
}

std::shared_ptr<AST> Parser::AssignmentStatement() {
    auto left = Variable();
    Token token = currentToken;
    Eat(Token::TokenType::ASSIGN);
    auto right = Expr();
    auto node = std::make_shared<Assign>(left, token, right);
    return node;
}

std::shared_ptr<AST> Parser::Variable() {
    auto node = std::make_shared<Var>(currentToken);
    Eat(Token::TokenType::ID);
    return node;
}

std::shared_ptr<AST> Parser::Empty() {
    return std::make_shared<NoOp>();
}

std::shared_ptr<AST> Parser::Factor() {
    Token token = currentToken;
    if (token.GetType() == Token::TokenType::PLUS) {
        Eat(Token::TokenType::PLUS);
        return std::make_shared<UnaryOp>(token, Factor());
    }
    else if (token.GetType() == Token::TokenType::MINUS) {
        Eat(Token::TokenType::MINUS);
        return std::make_shared<UnaryOp>(token, Factor());
    }
    else if (token.GetType() == Token::TokenType::INTEGER_CONST) {
        Eat(Token::TokenType::INTEGER_CONST);
        return std::make_shared<Num<int>>(token);
    }
    else if (token.GetType() == Token::TokenType::FLOAT_CONST) {
        Eat(Token::TokenType::FLOAT_CONST);
        return std::make_shared<Num<float>>(token);
    }
    else if (token.GetType() == Token::TokenType::LPAREN) {
        Eat(Token::TokenType::LPAREN);
        auto node = Expr();
        Eat(Token::TokenType::RPAREN);
        return node;
    }
    else {
        return Variable();
    }
}

std::shared_ptr<AST> Parser::Term() {
    auto node = Factor();

    while (currentToken.GetType() == Token::TokenType::MUL || currentToken.GetType() == Token::TokenType::DIV) {
        Token token = currentToken;
        if (currentToken.GetType() == Token::TokenType::MUL)
            Eat(Token::TokenType::MUL);
        else if (currentToken.GetType() == Token::TokenType::DIV)
            Eat(Token::TokenType::DIV);
        else
            throw std::exception("Invalid syntax");

        node = std::make_shared<BinOp>(node, token, Factor());
    }

    return node;
}

std::shared_ptr<AST> Parser::Expr() {
    auto node = Term();

    while (currentToken.GetType() == Token::TokenType::PLUS || currentToken.GetType() == Token::TokenType::MINUS) {
        Token token = currentToken;
        if (token.GetType() == Token::TokenType::PLUS)
            Eat(Token::TokenType::PLUS);
        else if (token.GetType() == Token::TokenType::MINUS)
            Eat(Token::TokenType::MINUS);
        else
            throw std::exception("Invalid syntax");

        node = std::make_shared<BinOp>(node, token, Term());
    }

    return node;
}

std::shared_ptr<AST> Parser::Parse() {
    auto node = Module();
    if (currentToken.GetType() != Token::TokenType::TOKENEOF) {
        Error();
    }

    return node;
}
