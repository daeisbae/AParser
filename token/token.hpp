#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <memory>
#include "file.hpp"
#include "operator.hpp"

enum class TokenType {
  EOL,
  INVALID,
  IDENTIFIER,
  INT,
  STRING,
  BOOL,
  IF,
  FOR,
  FUNCTION,
  RETURN,
  OPERATOR
};

class Token {
private:
  std::shared_ptr<File> srcfile;
  int ch_position;
  int ch_line;
  TokenType toktype;
  std::string literal;
  OperatorPtr op;

public:
  Token(std::shared_ptr<File> src_file, const std::string& input, int char_position, int char_line, TokenType toktype, OperatorPtr op);
  ~Token();

  TokenType Type() const;
  int CharPosition() const;
  int CharLine() const;
  std::string Text() const;
};

typedef std::shared_ptr<Token> TokenPtr;

TokenPtr GenerateToken(std::shared_ptr<File> src_file, const std::string& input, int char_position, int char_line, TokenType toktype, OperatorPtr op);

#endif