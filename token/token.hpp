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
  WHITESPACE,
  SET,
  INTEGER,
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
  TokenType toktype;
  std::string value;
  OperatorPtr op;

public:
  Token(const std::string& input, TokenType toktype, OperatorPtr op);
  ~Token();

  TokenType Type() const;
  std::string Text() const;

  bool operator==(const Token& token) {
    return Type() == token.Type() && Text() == token.Text();
  };
};

typedef std::shared_ptr<Token> TokenPtr;

TokenPtr GenerateToken(const std::string& input, TokenType toktype, OperatorPtr op);

#endif