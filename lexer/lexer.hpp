#ifndef LEXER_H
#define LEXER_H

#include <queue>
#include <string>
#include <vector>

#include "file.hpp"
#include "operator.hpp"
#include "token.hpp"

class Lexer {
 private:
  FilePtr file_ptr_;
  std::queue<char> text_queue_;
  int line_;

  // Parse the string
  std::string ReadStr();
  // Parse the number
  std::string ReadNum();
  // Parse the literal (variable/function naming)
  std::string ReadLiteral();

  std::string ReadOp();

  std::string ReadWhitespace();

 public:
  Lexer(std::string input);
  Lexer(FilePtr file_ptr);
  ~Lexer();

  // Return the keyword into tokentype
  TokenType GetReservedKeywordTokenType(std::string keyword) const;

  // Return the next keyword in token pointer (TokenPtr)
  TokenPtr NextToken();
};

class WrongLexingException : public std::exception {
 private:
  std::string err_info_;

 public:
  WrongLexingException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

class LexLineOutOfBoundException : public std::exception {
 private:
  std::string err_info_;

 public:
  LexLineOutOfBoundException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

class NullFileMemberException : public std::exception {
 private:
  std::string err_info_;

 public:
  NullFileMemberException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

#endif