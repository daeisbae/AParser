/**
 * @file parser.hpp
 * @brief Contains the Parser class and its helper classes.
 * Converts the list of Tokens to AST nodes (Statement and Expression).
 */
#ifndef PARSER_H
#define PARSER_H

#include <queue>

#include "ast.hpp"
#include "token.hpp"

/**
 * @brief The Parser class that takes in a queue of Token and produces an AST Statement and Expression
 */
class Parser {
 private:
  std::queue<TokenPtr> tok_queue_;

  /**
   * @brief Preview the next token
   */
  TokenPtr Peek();

  /**
   * @brief Check if the next token is the expected TokenType
   * @param expected_tok_type the expected TokenType
   * @return TokenPtr the next token
   */
  TokenPtr ExpectedTokenType(TokenType expected_tok_type);

  /**
   * @brief Check if the next token is the expected OperatorType
   * @param expected_op_type the expected OperatorType
   * @return TokenPtr the next token
   */
  TokenPtr ExpectedTokenType(OperatorType expected_op_type);

  /**
   * @brief Return the peeked value and pops the tok_queue (Token Queue)
   * @return TokenPtr the next token
   */
  TokenPtr Eat();

  /**
   * @brief Parse the program
   * @return Program the AST Program
   */
  StatementPtr ParseStatement();
  /**
   * @brief Parse the Expression
   * @return The Expression parsed
   */
  ExpressionPtr ParseExpression();

  /**
   * @brief Reads the token and assign the value as expression
   * @return ExpressionPtr the expression parsed
   */
  ExpressionPtr ParsePrimaryExpression();

  /**
   * @brief Parse the addition and subtraction operations
   * @return ExpressionPtr the expression parsed
   */
  ExpressionPtr ParseAdditionExpression();

  /**
   * @brief Parse the multiplication and division operations
   * @return ExpressionPtr the expression parsed
   */
  ExpressionPtr ParseMultiplicationExpression();

  /**
   * @brief Parse the whitespaces
   * @return ExpressionPtr the expression parsed
   */
  ExpressionPtr ParseWhitespaceExpression();

  /**
   * @brief Parse the identifier declaration (Refer: Evaluater::EvaluateDefiningIdentifierExpression)
   * @return StatementPtr the statement parsed
   */
  StatementPtr ParseIdentifierDeclarationExpression();

  /**
   * @brief Parse the identifier assignment (Refer: Evaluater::EvaluateAssignIdentifierExpression)
   * @return ExpressionPtr the statement parsed
   */
  ExpressionPtr ParseIdentifierAssignmentExpression();

  /**
   * @brief Parse the comparison operations
   * @return ExpressionPtr the expression parsed
   */
  ExpressionPtr ParseComparisonExpression();

 public:
  /**
   * @brief Construct a new Parser object
   */
  Parser();
  ~Parser();

  /**
   * @brief Convert the List of Tokens to List of AST nodes(Statement and Expression).
   * @param tokenQueue the Token queue to be converted to list of AST nodes (Statement and Expression)
   * @return Program the list of AST (Statements and Expressions)
   */
  Program ProduceAST(std::queue<TokenPtr> &tokenQueue);
};

/**
 * @brief The UnexpectedTokenParsedException class thrown when an Token is expected but another Token is parsed
 */
class UnexpectedTokenParsedException : public std::exception {
 private:
  std::string err_info_;

 public:
  UnexpectedTokenParsedException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

#endif
