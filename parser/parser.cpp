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

TokenPtr Parser::peek() { return tokqueue.front(); }

TokenPtr Parser::expectedTokenType(OperatorType expectedOpType) {
  TokenPtr currtok = peek();
  std::stringstream ssInvalidTokMsg;

  if (currtok->OpPtr()->Type() == expectedOpType) return currtok;

  ssInvalidTokMsg << "Expected: \')\' Got Operator: \'" << *(currtok->OpPtr())
                  << "\' is not allowed";
  throw UnexpectedTokenParsedException(ssInvalidTokMsg.str());
}

TokenPtr Parser::expectedTokenType(TokenType expectedTokType) {
  TokenPtr currtok = peek();
  std::stringstream ssInvalidTokMsg;

  if (currtok->Type() == expectedTokType) return currtok;
  ssInvalidTokMsg << "Expected: \')\' Got Token: \'" << *(currtok)
                  << "\' is not allowed";

  throw UnexpectedTokenParsedException(ssInvalidTokMsg.str());
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
  std::stringstream ssInvalidTokMsg;
  ExpressionPtr returnedExpr;

  // How it works: Read one token (then pop the queue) to convert to an
  // expression.
  switch (peek()->Type()) {
    case TokenType::IDENTIFIER:
      returnedExpr = ExpressionPtr(new IdentifierExpression(eat()->Text()));
      break;
    case TokenType::INTEGER:
      returnedExpr =
          ExpressionPtr(new IntegerExpression(std::stoi(eat()->Text())));
      break;
    case TokenType::WHITESPACE:
      returnedExpr = ExpressionPtr(new WhitespaceExpression(eat()->Text()));
      break;
    case TokenType::NULLABLE:
      eat();
      returnedExpr = ExpressionPtr(new NullExpression());
      break;
    case TokenType::OPERATOR:
      switch (peek()->OpPtr()->Type()) {
        case OperatorType::L_PARENTHESIS:
          eat();
          parseWhitespaceExpression();
          returnedExpr = parseExpression();
          parseWhitespaceExpression();
          expectedTokenType(OperatorType::R_PARENTHESIS);
          eat();
          break;
        default:
          ssInvalidTokMsg << "Unexpected Operator: \'" << *(peek()->OpPtr())
                          << "\' is not allowed";
          throw UnexpectedTokenParsedException(ssInvalidTokMsg.str());
      };
      break;
    default:
      ssInvalidTokMsg << "Unexpected Token: \'" << *peek()
                      << "\' is not allowed";
      throw UnexpectedTokenParsedException(ssInvalidTokMsg.str());
      break;
  }
  return returnedExpr;
}

ExpressionPtr Parser::parseAdditionExpression() {
  ExpressionPtr left = parseMultiplicationExpression();
  parseWhitespaceExpression();

  while (peek()->Type() != TokenType::EOL &&
         (peek()->OpPtr()->Type() == OperatorType::PLUS ||
          peek()->OpPtr()->Type() == OperatorType::MINUS)) {
    const std::string opVal = eat()->Text();
    parseWhitespaceExpression();
    ExpressionPtr right = parseMultiplicationExpression();
    parseWhitespaceExpression();

    left = ExpressionPtr(new BinaryExpression(left, opVal, right));
  }

  return left;
}

ExpressionPtr Parser::parseMultiplicationExpression() {
  ExpressionPtr left = parsePrimaryExpression();
  parseWhitespaceExpression();

  while (peek()->Type() != TokenType::EOL &&
         (peek()->OpPtr()->Type() == OperatorType::STAR ||
          peek()->OpPtr()->Type() == OperatorType::SLASH)) {
    const std::string opVal = eat()->Text();
    parseWhitespaceExpression();
    ExpressionPtr right = parsePrimaryExpression();
    parseWhitespaceExpression();

    left = ExpressionPtr(new BinaryExpression(left, opVal, right));
  }

  return left;
}

ExpressionPtr Parser::parseWhitespaceExpression() {
  TokenPtr currTok = tokqueue.front();
  if (currTok->Type() == TokenType::WHITESPACE)
    return ExpressionPtr(new WhitespaceExpression(eat()->Text()));

  return ExpressionPtr(nullptr);
}