#include "lexer.hpp"

#include <cctype>
#include <sstream>
#include <string>

#include "file.hpp"
#include "iostream"
#include "stringutil.hpp"
#include "token.hpp"

Lexer::Lexer(FilePtr file_ptr) {
  file_ptr_ = file_ptr;
  line_ = 1;
  text_queue_ = ConvertStringToQueue(file_ptr_->Read());
}

Lexer::Lexer(std::string input) {
  text_queue_ = ConvertStringToQueue(input);
  line_ = 1;
}

Lexer::~Lexer() {}

std::string Lexer::ReadStr() {
  if (text_queue_.front() != '\"')
    throw WrongLexingException("Double quote for string not found");

  // Pop the double quote (starting point of the string)
  text_queue_.pop();

  std::string str_val;

  while (!text_queue_.empty()) {
    if (text_queue_.front() == '\0') {
      std::stringstream ssInvalidStrMsg;
      ssInvalidStrMsg << "Ending double quote not found after \"" << str_val
                      << "\"";
      throw WrongLexingException(ssInvalidStrMsg.str());
    }

    // If it is the ending double quote of the string
    if (text_queue_.front() == '\"' && str_val.back() != '\\') break;

    // If it is the double quote inside the string
    if (text_queue_.front() == '\"' && str_val.back() == '\\')
      str_val.pop_back();

    str_val.push_back(text_queue_.front());
    text_queue_.pop();
  }

  text_queue_.pop();

  return str_val;
}

std::string Lexer::ReadNum() {
  std::string num_val;

  while (!text_queue_.empty() && std::isdigit(text_queue_.front())) {
    num_val.push_back(text_queue_.front());
    text_queue_.pop();
  };

  return num_val;
}

std::string Lexer::ReadLiteral() {
  std::string str_val;

  if (!isalpha(text_queue_.front()))
    throw WrongLexingException("Alphabet not found");
  str_val.push_back(text_queue_.front());
  text_queue_.pop();

  while (!text_queue_.empty() && isalnum(text_queue_.front())) {
    str_val.push_back(text_queue_.front());
    text_queue_.pop();
  }

  return str_val;
}

std::string Lexer::ReadOp() {
  std::string allowed_op = "(){}!=+-*/";
  if (allowed_op.find(text_queue_.front()) == std::string::npos)
    throw WrongLexingException("Allowed Operator not found");

  std::string op_str;
  op_str.push_back(text_queue_.front());
  text_queue_.pop();

  bool isMultiplePunctuationAllowed = Operator(op_str).IsOverloadable();

  // This design will let 1-2 chars of punct in one operator.
  if (!isMultiplePunctuationAllowed) return op_str;

  op_str.push_back(text_queue_.front());

  // Constructor validate Operator punctuation. if err, remove the operator
  try {
    Operator optest(op_str);
    text_queue_.pop();
  } catch (InvalidOperatorTypeException) {
    op_str.pop_back();
  }

  return op_str;
}

std::string Lexer::ReadWhitespace() {
  std::string str_val;
  if (!isspace(text_queue_.front()))
    throw WrongLexingException("Whitespace not found");

  while (!text_queue_.empty() && isspace(text_queue_.front())) {
    str_val.push_back(text_queue_.front());
    text_queue_.pop();
  }

  return str_val;
}

TokenType Lexer::GetReservedKeywordTokenType(std::string keyword) const {
  if (keyword == "func") return TokenType::FUNCTION;
  if (keyword == "if") return TokenType::IF;
  if (keyword == "set") return TokenType::SET;
  if (keyword == "true") return TokenType::TRUE;
  if (keyword == "false") return TokenType::FALSE;
  if (keyword == "for") return TokenType::FOR;
  if (keyword == "return") return TokenType::RETURN;
  if (keyword == "null") return TokenType::NULLABLE;

  return TokenType::INVALID;
}

TokenPtr Lexer::NextToken() {
  TokenPtr tok_ptr;

  TokenType tok_type;
  // Check whether it is for literal or number
  std::string text_val;

  switch (static_cast<int>(text_queue_.front())) {
    case 0:  // NULL terminator
      tok_ptr = GenerateToken("", TokenType::EOL, OperatorPtr(nullptr));
      break;
    case 9:   // \t
    case 32:  // Space
      tok_ptr = GenerateToken(ReadWhitespace(), TokenType::WHITESPACE,
                              OperatorPtr(nullptr));
      break;
    case 33:   // !
    case 40:   // (
    case 41:   // )
    case 42:   // *
    case 43:   // +
    case 45:   // -
    case 47:   // /
    case 61:   // =
    case 123:  // {
    case 125:  // }
      text_val = ReadOp();
      tok_ptr =
          GenerateToken(text_val, TokenType::OPERATOR, GenerateOp(text_val));
      break;
    case 34:  // "
      tok_ptr =
          GenerateToken(ReadStr(), TokenType::STRING, OperatorPtr(nullptr));
      break;
    case 48 ... 57:  // 0-9
      // Validate if it is number
      tok_ptr =
          GenerateToken(ReadNum(), TokenType::INTEGER, OperatorPtr(nullptr));
      break;
    case 65 ... 90:   // A-Z
    case 97 ... 122:  // a-z
      // Validate reserved string or if it is identifier
      text_val = ReadLiteral();
      tok_type = GetReservedKeywordTokenType(text_val);
      if (tok_type == TokenType::INVALID) {
        tok_ptr = GenerateToken(text_val, TokenType::IDENTIFIER,
                                OperatorPtr(nullptr));
      } else {
        tok_ptr = GenerateToken(text_val, tok_type, OperatorPtr(nullptr));
      }
      break;
    default:
      std::stringstream ssInvalidTokMsg;
      ssInvalidTokMsg << "Token: \'" << text_queue_.front()
                      << "\' is not allowed";
      throw WrongLexingException(ssInvalidTokMsg.str());
  }

  return tok_ptr;
}