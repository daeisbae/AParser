#include "token.hpp"

Token::Token(const std::string& input, TokenType toktype, OperatorPtr op) {
  this->value = input;
  this->toktype = toktype;
  this->op = op;
};

Token::~Token(){

};

TokenType Token::Type() const { return toktype; }

std::string Token::Text() const { return value; }

std::string Token::PrintTokenType(TokenType toktype) {
  switch (toktype) {
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
    default:
      return "Unidentified Token";
  }
}

TokenPtr GenerateToken(const std::string& input, TokenType toktype,
                       OperatorPtr op) {
  return TokenPtr(new Token(input, toktype, op));
}