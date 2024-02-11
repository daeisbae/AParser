#ifndef PARSER_H
#define PARSER_H

#include <queue>

#include "ast.hpp"
#include "token.hpp"

class Parser {
 private:
  std::queue<TokenPtr> tokqueue;

  // Return the peeked value and pops the tokqueue
  TokenPtr eat();

  StatementPtr parseStatement();
  ExpressionPtr parseExpression();
  ExpressionPtr parsePrimaryExpression();
  ExpressionPtr parseAdditionExpression();

 public:
  Parser(std::queue<TokenPtr> tokenQueue);
  ~Parser();

  Program ProduceAST();
};

class UnexpectedTokenParsedException : public std::exception {
 private:
  std::string errinfo;

 public:
  UnexpectedTokenParsedException(std::string err) : errinfo(err){};

  const char* what() const noexcept override { return errinfo.c_str(); }
};

#endif