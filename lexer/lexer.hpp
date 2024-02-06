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
  FilePtr file;
  std::queue<char> textqueue;
  int line;

  // Parse the string
  std::string readStr();
  // Parse the number
  std::string readNum();
  // Parse the literal (variable/function naming)
  std::string readLiteral();

  std::string readWhitespace();

 public:
  Lexer(std::string input);
  Lexer(FilePtr fileptr);
  ~Lexer();

  // Return the keyword into tokentype
  TokenType GetReservedKeywordTokenType(std::string keyword) const;

  // Return the next keyword in token pointer (TokenPtr)
  TokenPtr NextToken();

  // If there's file member, read next line.
  void ReadNextLine();
};

class WrongLexingException : public std::exception {
 private:
  std::string errinfo;

 public:
  WrongLexingException(std::string err) : errinfo(err){};

  const char* what() const noexcept override { return errinfo.c_str(); }
};

class LexLineOutOfBoundException : public std::exception {
 private:
  std::string errinfo;

 public:
  LexLineOutOfBoundException(std::string err) : errinfo(err){};

  const char* what() const noexcept override { return errinfo.c_str(); }
};

class NullFileMemberException : public std::exception {
 private:
  std::string errinfo;

 public:
  NullFileMemberException(std::string err) : errinfo(err){};

  const char* what() const noexcept override { return errinfo.c_str(); }
};

#endif