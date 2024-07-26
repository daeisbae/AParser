/**
 * @file lexer.hpp
 * @brief Lexer Class and it's association Exceptions related to lexers
 */
#ifndef LEXER_H
#define LEXER_H

#include <queue>
#include <string>
#include <vector>

#include "file.hpp"
#include "operator.hpp"
#include "token.hpp"

/**
 * @brief Lexer class to parse the input string
 */
class Lexer {
 private:
  FilePtr file_ptr_;
  std::queue<char> text_queue_;
  int line_;

  /**
   * @brief Lex the string between the quotation marks
   * @return std::string the string between the quotation marks
   */
  std::string ReadStr();
  /**
   * @brief Lex the number
   * @return std::string lex number in string format
   */
  std::string ReadNum();
  /**
   * @brief Lex the literal (variable name, function name, etc.)
   * @return std::string lex literal
   */
  std::string ReadLiteral();

  /**
   * @brief Lex the operator
   * @return std::string lex operator
   */
  std::string ReadOp();

  /**
   * @brief Lex the whitespace
   * @return std::string lex whitespace
   */
  std::string ReadWhitespace();

 public:
  /**
   * @brief Construct a new Lexer object
   * @param input the input string to be lexed
   */
  Lexer(std::string input);
  Lexer(FilePtr file_ptr);
  ~Lexer();

  /**
   * @brief Check if the keyword is a reserved keyword
   * @return TokenType the token type of the reserved keyword, else TokenType::INVALID
   */
  TokenType GetReservedKeywordTokenType(std::string keyword) const;

  /**
   * @brief Get the next token in the input string using the Read... functions
   * @return TokenPtr the next token in the input string
   */
  TokenPtr NextToken();
};

/**
 * @brief Exceptions if the lexer lex can't find the correct token
 */
class WrongLexingException : public std::exception {
 private:
  std::string err_info_;

 public:
  WrongLexingException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

/**
 * @brief Exceptions if the lexer lex went out of bound
 */
class LexLineOutOfBoundException : public std::exception {
 private:
  std::string err_info_;

 public:
  LexLineOutOfBoundException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

/**
 * @brief Exceptions if the file member does not exist
 */
class NullFileMemberException : public std::exception {
 private:
  std::string err_info_;

 public:
  NullFileMemberException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

#endif
