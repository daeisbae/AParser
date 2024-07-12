#include "parser.hpp"

#include <memory>
#include <sstream>

#include "ast.hpp"

Parser::Parser(){};
Parser::~Parser(){};

TokenPtr Parser::Eat() {
  TokenPtr token = tok_queue_.front();
  tok_queue_.pop();
  return token;
}

TokenPtr Parser::Peek() { return tok_queue_.front(); }

TokenPtr Parser::ExpectedTokenType(OperatorType expected_type) {
  TokenPtr curr_tok = Peek();
  std::stringstream invalid_tok_msg;

  if (curr_tok->OpPtr()->Type() == expected_type) return curr_tok;

  invalid_tok_msg << "Expected: \')\' Got Operator: \'" << *(curr_tok->OpPtr())
                  << "\' is not allowed";
  throw UnexpectedTokenParsedException(invalid_tok_msg.str());
}

TokenPtr Parser::ExpectedTokenType(TokenType expected_type) {
  TokenPtr curr_tok = Peek();
  std::stringstream invalid_tok_msg;

  if (curr_tok->Type() == expected_type) return curr_tok;
  invalid_tok_msg << "Expected: \')\' Got Token: \'" << *(curr_tok)
                  << "\' is not allowed";

  throw UnexpectedTokenParsedException(invalid_tok_msg.str());
}

Program Parser::ProduceAST(std::queue<TokenPtr> &tok_queue) {
  tok_queue_ = tok_queue;
  Program program = Program();

  while (tok_queue_.front()->Type() != TokenType::EOL) {
    program.body_.push(ParseStatement());
  }

  // Remove TokenType::EOL
  Eat();

  return program;
}

StatementPtr Parser::ParseStatement() {
  switch (Peek()->Type()) {
    case TokenType::SET:
      return ParseIdentifierDeclarationExpression();
    default:
      return ParseExpression();
  }
}

ExpressionPtr Parser::ParseExpression() {
  return ParseIdentifierAssignmentExpression();
}

ExpressionPtr Parser::ParsePrimaryExpression() {
  std::stringstream ssInvalidTokMsg;
  ExpressionPtr returned_expr;

  // How it works: Read one token (then pop the queue) to convert to an
  // expression.

  TokenPtr curr_tok = Peek();
  switch (curr_tok->Type()) {
    case TokenType::IDENTIFIER:
      returned_expr = ExpressionPtr(new IdentifierExpression(Eat()->Text()));
      break;
    case TokenType::NUMBER:
      returned_expr =
          ExpressionPtr(new NumberExpression(std::stod(Eat()->Text())));
      break;
    case TokenType::WHITESPACE:
      returned_expr = ExpressionPtr(new WhitespaceExpression(Eat()->Text()));
      break;
    case TokenType::NULLABLE:
      Eat();
      returned_expr = ExpressionPtr(new NullExpression());
      break;
    case TokenType::TRUE:
    case TokenType::FALSE:
      returned_expr = ExpressionPtr(new BooleanExpression(Eat()->Text()));
      break;
    case TokenType::OPERATOR:
      switch (Peek()->OpPtr()->Type()) {
        case OperatorType::L_PARENTHESIS:
          Eat();
          ParseWhitespaceExpression();
          returned_expr = ParseExpression();
          ParseWhitespaceExpression();
          ExpectedTokenType(OperatorType::R_PARENTHESIS);
          Eat();
          break;
        case OperatorType::PLUS:
        case OperatorType::MINUS: {
          int sign = 1;
          while (Peek()->Type() == TokenType::OPERATOR &&
                 (Peek()->OpPtr()->Type() == OperatorType::PLUS ||
                  Peek()->OpPtr()->Type() == OperatorType::MINUS)) {
            if (Peek()->OpPtr()->Type() == OperatorType::MINUS) {
              sign *= -1;
            }
            Eat();
            ParseWhitespaceExpression();
          }
          ExpectedTokenType(TokenType::NUMBER);
          returned_expr = ExpressionPtr(
              new NumberExpression(sign * std::stod(Eat()->Text())));
          break;
        }
        default:
          ssInvalidTokMsg << "Unexpected Operator: \'" << *(curr_tok->OpPtr())
                          << "\' is not allowed";
          throw UnexpectedTokenParsedException(ssInvalidTokMsg.str());
      };
      break;
    default:
      ssInvalidTokMsg << "Unexpected Token: \'" << *curr_tok
                      << "\' is not allowed";
      throw UnexpectedTokenParsedException(ssInvalidTokMsg.str());
      break;
  }
  return returned_expr;
}

ExpressionPtr Parser::ParseAdditionExpression() {
  ExpressionPtr left = ParseMultiplicationExpression();
  ParseWhitespaceExpression();

  TokenPtr curr_tok = Peek();
  while (curr_tok->Type() == TokenType::OPERATOR &&
         (curr_tok->OpPtr()->Type() == OperatorType::PLUS ||
          curr_tok->OpPtr()->Type() == OperatorType::MINUS)) {
    const std::string op_val = Eat()->Text();
    ParseWhitespaceExpression();
    ExpressionPtr right = ParseMultiplicationExpression();
    ParseWhitespaceExpression();

    left = ExpressionPtr(new BinaryExpression(left, op_val, right));
    curr_tok = Peek();
  }

  return left;
}

ExpressionPtr Parser::ParseMultiplicationExpression() {
  ExpressionPtr left = ParsePrimaryExpression();
  ParseWhitespaceExpression();

  TokenPtr curr_tok = Peek();
  while (curr_tok->Type() == TokenType::OPERATOR &&
         (curr_tok->OpPtr()->Type() == OperatorType::STAR ||
          curr_tok->OpPtr()->Type() == OperatorType::SLASH)) {
    const std::string op_val = Eat()->Text();
    ParseWhitespaceExpression();
    ExpressionPtr right = ParsePrimaryExpression();
    ParseWhitespaceExpression();

    left = ExpressionPtr(new BinaryExpression(left, op_val, right));
    curr_tok = Peek();
  }

  return left;
}

ExpressionPtr Parser::ParseWhitespaceExpression() {
  if (Peek()->Type() == TokenType::WHITESPACE)
    return ExpressionPtr(new WhitespaceExpression(Eat()->Text()));

  return ExpressionPtr(nullptr);
}

StatementPtr Parser::ParseIdentifierDeclarationExpression() {
  ExpectedTokenType(TokenType::SET);
  Eat();
  ParseWhitespaceExpression();

  ExpressionPtr parsedVar = ParsePrimaryExpression();
  std::shared_ptr<IdentifierExpression> var_expr =
      std::dynamic_pointer_cast<IdentifierExpression>(parsedVar);
  ParseWhitespaceExpression();

  if (Peek()->Type() == TokenType::EOL)
    return std::make_shared<VariableDeclarationStatement>(
        var_expr->identifier_);

  ExpectedTokenType(OperatorType::ASSIGN);
  Eat();
  ParseWhitespaceExpression();

  ExpressionPtr value = ParseExpression();
  ParseWhitespaceExpression();

  return std::make_shared<VariableDeclarationStatement>(var_expr->identifier_,
                                                        value);
}

ExpressionPtr Parser::ParseIdentifierAssignmentExpression() {
  // Can be an identifier
  ExpressionPtr left = ParseComparisonExpression();

  ParseWhitespaceExpression();

  TokenPtr curr_tok = Peek();
  if (curr_tok->Type() == TokenType::OPERATOR &&
      curr_tok->OpPtr()->Type() == OperatorType::ASSIGN) {
    Eat();

    ParseWhitespaceExpression();

    std::shared_ptr<IdentifierExpression> var_expr =
        std::dynamic_pointer_cast<IdentifierExpression>(left);

    ExpressionPtr value = ParseIdentifierAssignmentExpression();
    ParseWhitespaceExpression();

    return std::make_shared<VariableAssignExpression>(var_expr->identifier_,
                                                      value);
  }

  return left;
}

ExpressionPtr Parser::ParseComparisonExpression() {
  ExpressionPtr left = ParseAdditionExpression();
  ParseWhitespaceExpression();

  TokenPtr next_tok = Peek();
  while (next_tok->Type() == TokenType::OPERATOR &&
         (next_tok->OpPtr()->Type() == OperatorType::NOT_EQUAL ||
          next_tok->OpPtr()->Type() == OperatorType::EQUAL)) {
    const std::string op_val = Eat()->Text();
    ParseWhitespaceExpression();
    ExpressionPtr right = ParsePrimaryExpression();
    ParseWhitespaceExpression();

    left = ExpressionPtr(new ComparisonExpression(left, op_val, right));
    next_tok = Peek();
  }

  return left;
}
