#include "token.hpp"

Token::Token(const std::string &input, TokenType tok_type, OperatorPtr op) {
  value_ = input;
  tok_type_ = tok_type;
  op_ = op;
};

Token::~Token(){

};

TokenType Token::Type() const { return tok_type_; }

std::string Token::Text() const { return value_; }

OperatorPtr Token::OpPtr() const { return op_; }

std::string Token::PrintTokenType(TokenType tok_type) {
  switch (tok_type) {
    case TokenType::EOL:
      return "End of line";
    case TokenType::INVALID:
      return "Invalid";
    case TokenType::IDENTIFIER:
      return "Identifier";
    case TokenType::WHITESPACE:
      return "Whitespace";
    case TokenType::SET:
      return "Set";
    case TokenType::INTEGER:
      return "Integer";
    case TokenType::STRING:
      return "String";
    case TokenType::TRUE:
      return "True";
    case TokenType::FALSE:
      return "False";
    case TokenType::IF:
      return "If";
    case TokenType::FOR:
      return "For";
    case TokenType::FUNCTION:
      return "Function";
    case TokenType::RETURN:
      return "Return";
    case TokenType::OPERATOR:
      return "Operator";
    case TokenType::NULLABLE:
      return "Null";
    default:
      return "Unidentified Token";
  }
}

TokenPtr GenerateToken(const std::string &input, TokenType tok_type,
                       OperatorPtr op) {
  return TokenPtr(new Token(input, tok_type, op));
}