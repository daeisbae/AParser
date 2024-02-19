#ifndef PARSER_H
#define PARSER_H

#include <queue>

#include "ast.hpp"
#include "token.hpp"

class Parser {
 private:
  std::queue<TokenPtr> tokqueue;

  // Preview the next token
  TokenPtr peek();

  // Check if the token matches the expected TokenType | OperatorType
  // If it match, return TokenPtr
  // Else throw Exception
  TokenPtr expectedTokenType(TokenType expectedTokType);
  TokenPtr expectedTokenType(OperatorType expectedOpType);

  // Return the peeked value and pops the tokqueue
  TokenPtr eat();

  StatementPtr parseStatement();
  ExpressionPtr parseExpression();

  // Reads the token and assign the value as expression
  ExpressionPtr parsePrimaryExpression();

  // + and - operations
  ExpressionPtr parseAdditionExpression();

  // * and / operations
  ExpressionPtr parseMultiplicationExpression();

  // Read whitespaces if it exists
  ExpressionPtr parseWhitespaceExpression();

  // Declaration Identifier
  StatementPtr parseIdentifierDeclarationExpression();

  // Assignment Identifier
  ExpressionPtr parseIdentifierAssignmentExpression();

 public:
  Parser();
  ~Parser();

  Program ProduceAST(std::queue<TokenPtr>& tokenQueue);
};

class UnexpectedTokenParsedException : public std::exception {
 private:
  std::string errinfo;

 public:
  UnexpectedTokenParsedException(std::string err) : errinfo(err){};

  const char* what() const noexcept override { return errinfo.c_str(); }
};

#endif