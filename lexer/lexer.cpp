#include "lexer.hpp"

#include <cctype>
#include <sstream>
#include <string>

#include "file.hpp"
#include "iostream"
#include "stringutil.hpp"
#include "token.hpp"

Lexer::Lexer(FilePtr fileptr) {
  this->file = fileptr;
  line = 1;
  textqueue = ConvertStringToQueue(fileptr->Read());
}

Lexer::Lexer(std::string input) {
  textqueue = ConvertStringToQueue(input);
  line = 1;
}

Lexer::~Lexer() {}

std::string Lexer::readStr() {
  if (textqueue.front() != '\"')
    throw WrongLexingException("Double quote for string not found");

  // Pop the double quote (starting point of the string)
  textqueue.pop();

  std::string str_val;

  while (!textqueue.empty()) {
    if(textqueue.front() == '\0') {
      std::stringstream ssInvalidStrMsg;
      ssInvalidStrMsg << "Ending double quote not found after \"" << str_val << "\"";
      throw WrongLexingException(ssInvalidStrMsg.str());
    } 

    // If it is the ending double quote of the string
    if(textqueue.front() == '\"' && str_val.back() != '\\') break;
    
    // If it is the double quote inside the string
    if(textqueue.front() == '\"' && str_val.back() == '\\') str_val.pop_back();

    str_val.push_back(textqueue.front());
    textqueue.pop();
  }

  textqueue.pop();

  return str_val;
}

std::string Lexer::readNum() {
  std::string num_val;

  while (!textqueue.empty() && std::isdigit(textqueue.front())) {
    num_val.push_back(textqueue.front());
    textqueue.pop();
  };

  return num_val;
}

std::string Lexer::readLiteral() {
  std::string str_val;

  if (!isalpha(textqueue.front()))
    throw WrongLexingException("Alphabet not found");
  str_val.push_back(textqueue.front());
  textqueue.pop();

  while (!textqueue.empty() && isalnum(textqueue.front())) {
    str_val.push_back(textqueue.front());
    textqueue.pop();
  }

  return str_val;
}

std::string Lexer::readOp() {
  std::string allowed_op = "(){}!=+-*/";
  if(allowed_op.find(textqueue.front()) == std::string::npos) throw WrongLexingException("Allowed Operator not found");

  std::string op_str;
  op_str.push_back(textqueue.front());
  textqueue.pop();

  bool isMultiplePunctuationAllowed = Operator(op_str).IsOverloadable();

  // This design will let 1-2 chars of punct in one operator.
  if(!isMultiplePunctuationAllowed) return op_str;

  op_str.push_back(textqueue.front());
  
  // Constructor validate Operator punctuation. if err, remove the operator 
  try {
    Operator optest(op_str);
    textqueue.pop();
  } catch(InvalidOperatorTypeException) {
    op_str.pop_back();
  }

  return op_str;
}

std::string Lexer::readWhitespace() {
  std::string str_val;
  if (!isspace(textqueue.front()))
    throw WrongLexingException("Whitespace not found");

  while (!textqueue.empty() && isspace(textqueue.front())) {
    str_val.push_back(textqueue.front());
    textqueue.pop();
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

  return TokenType::INVALID;
}

TokenPtr Lexer::NextToken() {
  TokenPtr tokptr;

  TokenType toktype;
  // Check whether it is for literal or number
  std::string textval;

  switch (static_cast<int>(textqueue.front())) {
    case 0:  // NULL terminator
      tokptr = GenerateToken("", TokenType::EOL, OperatorPtr(nullptr));
      break;
    case 9:   // \t
    case 32:  // Space
      tokptr = GenerateToken(readWhitespace(), TokenType::WHITESPACE,
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
      textval = readOp();
      tokptr = GenerateToken(textval, TokenType::OPERATOR, GenerateOp(textval));
      break;
    case 34:  // "
      tokptr =
          GenerateToken(readStr(), TokenType::STRING, OperatorPtr(nullptr));
      break;
    case 48 ... 57:  // 0-9
      // Validate if it is number
      tokptr =
          GenerateToken(readNum(), TokenType::INTEGER, OperatorPtr(nullptr));
      break;
    case 65 ... 90:   // A-Z
    case 97 ... 122:  // a-z
      // Validate reserved string or if it is identifier
      textval = readLiteral();
      toktype = GetReservedKeywordTokenType(textval);
      if (toktype == TokenType::INVALID) {
        tokptr =
            GenerateToken(textval, TokenType::IDENTIFIER, OperatorPtr(nullptr));
      } else {
        tokptr = GenerateToken(textval, toktype, OperatorPtr(nullptr));
      }
      break;
    default:
      std::stringstream ssInvalidTokMsg;
      ssInvalidTokMsg << "Token: \'" << textqueue.front()
                      << "\' is not allowed";
      throw WrongLexingException(ssInvalidTokMsg.str());
      break;
  }

  return tokptr;
}