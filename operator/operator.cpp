#include "operator.hpp"

#include <sstream>

Operator::Operator(std::string input) {
  this->value = input;

  this->optype = GetOperatorType(input);

  fillOperatorMembers();
}

Operator::Operator(std::string input, OperatorType opType) {
  this->value = input;
  this->optype = opType;
  fillOperatorMembers();
}

Operator::~Operator(){};

OperatorType Operator::Type() const { return optype; }

std::string Operator::Text() const { return value; }

bool Operator::IsOverloadable() const { return overloadable; }

int Operator::Precedence() const { return precedence; }

void Operator::fillOperatorMembers() {
  switch (optype) {
    case OperatorType::STAR:
    case OperatorType::SLASH:
      precedence = 6;
      overloadable = false;
      break;
    case OperatorType::PLUS:
    case OperatorType::MINUS:
      precedence = 5;
      overloadable = false;
      break;
    case OperatorType::NOT:
      precedence = 5;
      overloadable = true;
      break;
    case OperatorType::L_PARENTHESIS:
    case OperatorType::R_PARENTHESIS:
      precedence = 4;
      overloadable = false;
      break;
    case OperatorType::L_BRACE:
    case OperatorType::R_BRACE:
      precedence = 3;
      overloadable = false;
      break;
    case OperatorType::ASSIGN:
      precedence = 2;
      overloadable = true;
      break;
    case OperatorType::EQUAL:
    case OperatorType::NOT_EQUAL:
      precedence = 1;
      overloadable = false;
      break;
    default:
      precedence = 7;
      overloadable = false;
  }
}

OperatorType Operator::GetOperatorType(std::string input) {
  if (input == "+")
    return OperatorType::PLUS;
  if (input == "-")
    return OperatorType::MINUS;
  if (input == "*")
    return OperatorType::STAR;
  if (input == "/")
    return OperatorType::SLASH;
  if (input == "(")
    return OperatorType::L_PARENTHESIS;
  if (input == ")")
    return OperatorType::R_PARENTHESIS;
  if (input == "{")
    return OperatorType::L_BRACE;
  if (input == "}")
    return OperatorType::R_BRACE;
  if (input == "=")
    return OperatorType::ASSIGN;
  if (input == "==")
    return OperatorType::EQUAL;
  if (input == "!")
    return OperatorType::NOT;
  if (input == "!=")
    return OperatorType::NOT_EQUAL;
  
  std::stringstream ssInvalidOpMsg;
  ssInvalidOpMsg << "Operator: \'" << input
                      << "\' is not allowed";
  throw InvalidOperatorTypeException(ssInvalidOpMsg.str());
}

OperatorPtr GenerateOp(const std::string& input) {
  return OperatorPtr(new Operator(input));
}

OperatorPtr GenerateOp(const std::string& input, OperatorType opType) {
  return OperatorPtr(new Operator(input, opType));
}