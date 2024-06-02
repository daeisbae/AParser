#ifndef PARSER_H
#define PARSER_H

#include <queue>

#include "ast.hpp"
#include "token.hpp"

class Parser {
 private:
  std::queue<TokenPtr> tok_queue_;

  // Preview the next token
  TokenPtr Peek();

  // Check if the token matches the expected TokenType | OperatorType
  // If it match, return TokenPtr
  // Else throw Exception
  TokenPtr ExpectedTokenType(TokenType expected_tok_type);
  TokenPtr ExpectedTokenType(OperatorType expected_op_type);

  // Return the peeked value and pops the tok_queue
  TokenPtr Eat();

  StatementPtr ParseStatement();
  ExpressionPtr ParseExpression();

  // Reads the token and assign the value as expression
  ExpressionPtr ParsePrimaryExpression();

  // + and - operations
  ExpressionPtr ParseAdditionExpression();

  // * and / operations
  ExpressionPtr ParseMultiplicationExpression();

  // Read whitespaces if it exists
  ExpressionPtr ParseWhitespaceExpression();

  // Declaration Identifier
  StatementPtr ParseIdentifierDeclarationExpression();

  // Assignment Identifier
  ExpressionPtr ParseIdentifierAssignmentExpression();

  // Comparison (== , !=)
  ExpressionPtr ParseComparisonExpression();

 public:
  Parser();
  ~Parser();

  Program ProduceAST(std::queue<TokenPtr> &tokenQueue);
};

class UnexpectedTokenParsedException : public std::exception {
 private:
  std::string err_info_;

 public:
  UnexpectedTokenParsedException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

#endif