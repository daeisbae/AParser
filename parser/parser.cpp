#include "parser.hpp"

#include <memory>
#include <sstream>

#include "ast.hpp"

Parser::Parser(){};
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

Program Parser::ProduceAST(std::queue<TokenPtr>& tokenQueue) {
  tokqueue = tokenQueue;
  Program program = Program();

  while (tokqueue.front()->Type() != TokenType::EOL) {
    program.Body.push(parseStatement());
  }

  // Remove TokenType::EOL
  eat();

  return program;
}

StatementPtr Parser::parseStatement() {
  TokenPtr currtok = peek();
  switch (currtok->Type()) {
    case TokenType::SET:
      return parseIdentifierDeclarationExpression();
    default:
      return parseExpression();
  }
}

ExpressionPtr Parser::parseExpression() {
  return parseIdentifierAssignmentExpression();
}

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
    case TokenType::TRUE:
    case TokenType::FALSE:
      returnedExpr = ExpressionPtr(new BooleanExpression(eat()->Text()));
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
        case OperatorType::PLUS:
        case OperatorType::MINUS: {
          int sign = 1;
          while (peek()->Type() == TokenType::OPERATOR &&
                 (peek()->OpPtr()->Type() == OperatorType::PLUS ||
                  peek()->OpPtr()->Type() == OperatorType::MINUS)) {
            if (peek()->OpPtr()->Type() == OperatorType::MINUS) {
              sign *= -1;
            }
            eat();
            parseWhitespaceExpression();
          }
          expectedTokenType(TokenType::INTEGER);
          returnedExpr = ExpressionPtr(
              new IntegerExpression(sign * std::stoi(eat()->Text())));
          break;
        }
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

  while (peek()->Type() == TokenType::OPERATOR &&
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

  while (peek()->Type() == TokenType::OPERATOR &&
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

StatementPtr Parser::parseIdentifierDeclarationExpression() {
  expectedTokenType(TokenType::SET);
  eat();
  parseWhitespaceExpression();

  ExpressionPtr parsedVar = parsePrimaryExpression();
  std::shared_ptr<IdentifierExpression> varExpr =
      std::dynamic_pointer_cast<IdentifierExpression>(parsedVar);
  parseWhitespaceExpression();

  if (peek()->Type() == TokenType::EOL)
    return std::make_shared<VariableDeclarationStatement>(varExpr->Name);

  expectedTokenType(OperatorType::ASSIGN);
  eat();
  parseWhitespaceExpression();

  ExpressionPtr value = parseExpression();
  parseWhitespaceExpression();

  return std::make_shared<VariableDeclarationStatement>(varExpr->Name, value);
}

ExpressionPtr Parser::parseIdentifierAssignmentExpression() {
  // Can be an identifier
  ExpressionPtr left = parseAdditionExpression();

  parseWhitespaceExpression();

  if (peek()->Type() == TokenType::OPERATOR &&
      peek()->OpPtr()->Type() == OperatorType::ASSIGN) {
    eat();

    parseWhitespaceExpression();

    std::shared_ptr<IdentifierExpression> varExpr =
        std::dynamic_pointer_cast<IdentifierExpression>(left);

    ExpressionPtr value = parseIdentifierAssignmentExpression();
    parseWhitespaceExpression();

    return std::make_shared<VariableAssignExpression>(varExpr->Name, value);
  }

  return left;
}