#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <string>

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
  TRUE,
  FALSE,
  IF,
  FOR,
  FUNCTION,
  RETURN,
  OPERATOR,
  NULLABLE
};

class Token {
 private:
  TokenType tok_type_;
  std::string value_;
  OperatorPtr op_;

 public:
  Token(const std::string &input, TokenType tok_type, OperatorPtr op);
  ~Token();

  TokenType Type() const;
  std::string Text() const;
  OperatorPtr OpPtr() const;

  static std::string PrintTokenType(TokenType tok_type);

  bool operator==(const Token &token) const {
    return Type() == token.Type() && Text() == token.Text();
  };

  friend std::ostream &operator<<(std::ostream &out, const Token &token) {
    out << "Token( TokenType: " << PrintTokenType(token.Type()) << " Value: \'"
        << token.value_ << "\' )";
    return out;
  }
};

typedef std::shared_ptr<Token> TokenPtr;

TokenPtr GenerateToken(const std::string &input, TokenType tok_type,
                       OperatorPtr op);

#endif