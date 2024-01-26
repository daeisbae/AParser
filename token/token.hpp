#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <memory>
#include "file.hpp"
#include "operator.hpp"

class File;

class Token {
private:
  enum TokenType {
    EOL,
    INVALID,
    IDENTIFIER,
    INT,
    STRING,
    IF,
    FOR,
    FUNC,
    RETURN,
    TRUE,
    FALSE
  };

  std::shared_ptr<File> srcFile;
  int ch_position;
  int ch_line;
  TokenType toktype;
  std::string literal;

public:
  Token(std::shared_ptr<File> srcFile, const std::string& input, int charPosition, int charLine, TokenType tokType, OperatorPtr op);
  ~Token();

  TokenType TokenType() const;
  int CharPosition() const;
  std::string Text() const;
  int CharLine() const;
};

typedef std::shared_ptr<Token> TokenPtr;

#endif