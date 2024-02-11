#include "parser.hpp"

#include <sstream>

#include "ast.hpp"

Parser::Parser(std::queue<TokenPtr> tokenQueue) : tokqueue(tokenQueue) {}
Parser::~Parser(){};

TokenPtr Parser::eat() {
  TokenPtr token = tokqueue.front();
  tokqueue.pop();
  return token;
}

Program Parser::ProduceAST() {
  Program program = Program();

  while (tokqueue.front()->Type() != TokenType::EOL) {
    program.Body.push_back(parseStatement());
  }

  return program;
}

StatementPtr Parser::parseStatement() { return parseExpression(); }

ExpressionPtr Parser::parseExpression() { return parseAdditionExpression(); }

ExpressionPtr Parser::parsePrimaryExpression() {
  const TokenPtr currtok = tokqueue.front();
  ExpressionPtr returnedExpr;

  // How it works: Read one token (then pop the queue) to convert to an
  // expression.
  switch (currtok->Type()) {
    case TokenType::IDENTIFIER:
      returnedExpr = ExpressionPtr(new IdentifierExpression(eat()->Text()));
      break;
    case TokenType::INTEGER:
      returnedExpr =
          ExpressionPtr(new IntegerExpression(std::stoi(eat()->Text())));
      break;
    case TokenType::EOL:
      break;
    default:
      std::stringstream ssInvalidTokMsg;
      ssInvalidTokMsg << "Unexpected Token: \'" << *(currtok)
                      << "\' is not allowed";
      throw UnexpectedTokenParsedException(ssInvalidTokMsg.str());
      break;
  }
  return returnedExpr;
}

ExpressionPtr Parser::parseAdditionExpression() {
  ExpressionPtr left = parsePrimaryExpression();
  TokenPtr operatorExpectedTok = tokqueue.front();

  while (operatorExpectedTok->Type() != TokenType::EOL &&
         (operatorExpectedTok->OpPtr()->Type() == OperatorType::PLUS ||
          operatorExpectedTok->OpPtr()->Type() == OperatorType::MINUS)) {
    const std::string opVal = eat()->Text();
    ExpressionPtr right = parsePrimaryExpression();
    left = ExpressionPtr(new BinaryExpression(left, opVal, right));
    operatorExpectedTok = tokqueue.front();
  }

  return left;
}