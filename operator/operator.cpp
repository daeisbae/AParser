#include "operator.hpp"

Operator::Operator(std::string input) {
  this->value = input;

  if (input == "+")
    optype = OperatorType::PLUS;
  else if (input == "-")
    optype = OperatorType::MINUS;
  else if (input == "*")
    optype = OperatorType::STAR;
  else if (input == "/")
    optype = OperatorType::SLASH;
  else if (input == "(")
    optype = OperatorType::L_PARENTHESIS;
  else if (input == ")")
    optype = OperatorType::R_PARENTHESIS;
  else if (input == "{")
    optype = OperatorType::L_BRACE;
  else if (input == "}")
    optype = OperatorType::R_BRACE;
  else if (input == "=")
    optype = OperatorType::ASSIGN;
  else if (input == "==")
    optype = OperatorType::EQUAL;
  else if (input == "!=")
    optype = OperatorType::NOT_EQUAL;
  else
    optype = OperatorType::INVALID;

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

OperatorPtr GenerateOp(const std::string& input) {
  return OperatorPtr(new Operator(input));
}

OperatorPtr GenerateOp(const std::string& input, OperatorType opType) {
  return OperatorPtr(new Operator(input, opType));
}