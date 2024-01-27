#include "token.hpp"

Token::Token(std::shared_ptr<File> src_file, const std::string& input, int char_position, int char_line, TokenType toktype, OperatorPtr op) {
    this->srcfile = src_file;
    this->literal = input;
    this->ch_position = char_position;
    this->ch_line = char_line;
    this->toktype = toktype;
    this->op = op;
};

Token::~Token() {

};

TokenType Token::Type() const {
    return toktype;
}

int Token::CharPosition() const {
    return ch_position;
}

int Token::CharLine() const {
    return ch_line;
}

std::string Token::Text() const {
    return literal;
}

TokenPtr GenerateToken(std::shared_ptr<File> src_file, const std::string& input, int char_position, int char_line, TokenType toktype, OperatorPtr op) {
    return TokenPtr(new Token(src_file, input, char_position, char_line, toktype, op));
}