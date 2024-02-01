#include "token.hpp"

Token::Token(const std::string& input, TokenType toktype, OperatorPtr op) {
    this->value = input;
    this->toktype = toktype;
    this->op = op;
};

Token::~Token() {

};

TokenType Token::Type() const {
    return toktype;
}

std::string Token::Text() const {
    return value;
}

TokenPtr GenerateToken(const std::string& input, TokenType toktype, OperatorPtr op) {
    return TokenPtr(new Token(input, toktype, op));
}