#include "operator.hpp"

#include <sstream>

Operator::Operator(std::string input) {
  value_ = input;

  op_type_ = GetOperatorType(input);

  FillOperatorMembers();
}

Operator::Operator(std::string input, OperatorType op_type) {
  value_ = input;
  op_type_ = op_type;
  FillOperatorMembers();
}

Operator::~Operator(){};

OperatorType Operator::Type() const { return op_type_; }

std::string Operator::Text() const { return value_; }

bool Operator::IsOverloadable() const { return overloadable_; }

int Operator::Precedence() const { return precedence_; }

void Operator::FillOperatorMembers() {
  switch (op_type_) {
    case OperatorType::STAR:
    case OperatorType::SLASH:
      precedence_ = 6;
      overloadable_ = false;
      break;
    case OperatorType::PLUS:
    case OperatorType::MINUS:
      precedence_ = 5;
      overloadable_ = false;
      break;
    case OperatorType::NOT:
      precedence_ = 5;
      overloadable_ = true;
      break;
    case OperatorType::L_PARENTHESIS:
    case OperatorType::R_PARENTHESIS:
      precedence_ = 4;
      overloadable_ = false;
      break;
    case OperatorType::L_BRACE:
    case OperatorType::R_BRACE:
      precedence_ = 3;
      overloadable_ = false;
      break;
    case OperatorType::ASSIGN:
      precedence_ = 2;
      overloadable_ = true;
      break;
    case OperatorType::EQUAL:
    case OperatorType::NOT_EQUAL:
      precedence_ = 1;
      overloadable_ = false;
      break;
    default:
      precedence_ = 7;
      overloadable_ = false;
  }
}

OperatorType Operator::GetOperatorType(std::string input) {
  if (input == "+") return OperatorType::PLUS;
  if (input == "-") return OperatorType::MINUS;
  if (input == "*") return OperatorType::STAR;
  if (input == "/") return OperatorType::SLASH;
  if (input == "(") return OperatorType::L_PARENTHESIS;
  if (input == ")") return OperatorType::R_PARENTHESIS;
  if (input == "{") return OperatorType::L_BRACE;
  if (input == "}") return OperatorType::R_BRACE;
  if (input == "=") return OperatorType::ASSIGN;
  if (input == "==") return OperatorType::EQUAL;
  if (input == "!") return OperatorType::NOT;
  if (input == "!=") return OperatorType::NOT_EQUAL;

  std::stringstream ss_invalid_op_msg;
  ss_invalid_op_msg << "Operator: \'" << input << "\' is not allowed";
  throw InvalidOperatorTypeException(ss_invalid_op_msg.str());
}

OperatorPtr GenerateOp(const std::string &input) {
  return OperatorPtr(new Operator(input));
}

OperatorPtr GenerateOp(const std::string &input, OperatorType op_type) {
  return OperatorPtr(new Operator(input, op_type));
}