#include "token.hpp"

Token::Token::Token(std::shared_ptr<File> src_file, const std::string& input, int char_position, int char_line, TokenType toktype, OperatorPtr op=OperatorPtr(nullptr)) {
    this->srcfile = src_file;
    this->input = input;
    this->ch_position = char_position;
    this->ch_line = char_line;
    this->toktype = toktype;
    this->op = op;
}

Token::~Token() {

}

Token::TokenType TokenType() const {
    return toktype;
}

int CharPosition() const {
    return ch_position;
}

int CharLine() const {
    return ch_line;
}

std::string Text() const {
    return input;
}

TokenPtr GenerateToken(std::shared_ptr<File> src_file, const std::string& input, int char_position, int char_line,
                         TokenType toktype, OperatorPtr op=OperatorPtr(nullptr)) {
    return TokenPtr(new Token(std::shared_ptr<File> src_file, const std::string& input, int char_position, int char_line,
                             TokenType toktype, OperatorPtr op=OperatorPtr(nullptr)))
}