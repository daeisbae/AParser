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
  OperatorPtr OpPtr() const;

  static std::string PrintTokenType(TokenType toktype);

  bool operator==(const Token& token) const {
    return Type() == token.Type() && Text() == token.Text();
  };

  friend std::ostream& operator<<(std::ostream& out, const Token& token) {
    out << "Token( TokenType: " << PrintTokenType(token.toktype) << " Value: \'"
        << token.value << "\' )";
    return out;
  }
};

typedef std::shared_ptr<Token> TokenPtr;

TokenPtr GenerateToken(const std::string& input, TokenType toktype,
                       OperatorPtr op);

#endif