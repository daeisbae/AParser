#ifndef RUNTIME_H
#define RUNTIME_H

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "ast.hpp"

enum class ValueType { NULLABLE, NUMBER, BOOLEAN, STRING };

class RuntimeValue {
 public:
  virtual ValueType Type() const = 0;
  virtual std::string Value() const = 0;
  void PrintOstream(std::ostream &out) const { out << Value(); }
};

class NullValue : public RuntimeValue {
 public:
  NullValue(){};

  ValueType Type() const { return ValueType::NULLABLE; }
  std::string Value() const { return "null"; }
};

class NumberValue : public RuntimeValue {
 private:
  double number_;

 public:
  NumberValue(double number) : number_(number){};

  ValueType Type() const { return ValueType::NUMBER; }
  std::string Value() const { return MaxDecimalNumberInStr(); }

 private:
  // Return the number until the longest decimal point available
  std::string MaxDecimalNumberInStr() const {
    std::stringstream num_to_str;
    num_to_str << std::fixed << std::setprecision(16) << number_;
    int max_decimal = 0;

    std::string num_in_str = num_to_str.str();

    // If it is an integer, return as an integer
    if ((int)number_ == number_) {
      return std::to_string((int)number_);
    }

    std::string decimal_in_str = num_in_str.substr(num_in_str.find(".") + 1);

    for (std::string::size_type i = 0; i < decimal_in_str.size(); i++) {
      if (decimal_in_str.at(i) != '0') {
        max_decimal = i + 1;
      }
    }

    return num_in_str.substr(0, num_in_str.find(".") + max_decimal + 1);
  }
};

class BooleanValue : public RuntimeValue {
 private:
  std::string boolean_;

 public:
  BooleanValue(std::string boolean) : boolean_(boolean){};

  ValueType Type() const { return ValueType::BOOLEAN; }
  std::string Value() const { return boolean_; }
};

class StringValue : public RuntimeValue {
 private:
  std::string string_;

 public:
  StringValue(std::string string) : string_(string){};

  ValueType Type() const { return ValueType::STRING; }
  std::string Value() const { return string_; }
};

typedef std::shared_ptr<RuntimeValue> RuntimeValuePtr;

class Environment {
 private:
  std::unordered_map<std::string, RuntimeValuePtr> var_map_;

 public:
  Environment();
  void DefineVariable(std::string name, RuntimeValuePtr runtimeValue);
  void AssignVariable(std::string name, RuntimeValuePtr runtimeValue);
  RuntimeValuePtr GetRuntimeValue(std::string name);
};

class Evaluater {
 private:
  Program instructions_;
  Environment env_;

  RuntimeValuePtr EvaluateBinaryExpression(BinaryExpression bin_expr);
  NumberValue EvaluateNumericBinaryExpression(NumberValue lhs, NumberValue rhs,
                                              std::string op);
  RuntimeValuePtr EvaluateDefiningIdentifierExpression(
      VariableDeclarationStatement varDeclStmt);
  RuntimeValuePtr EvaluateAssignIdentifierExpression(
      VariableAssignExpression varAssignExpr);
  RuntimeValuePtr EvaluateComparisonExpression(
      ComparisonExpression compareExpr);
  RuntimeValuePtr Evaluate(StatementPtr currStmt);

 public:
  Evaluater();

  std::string EvaluateProgram(Program instructions);
};

class UnexpectedStatementException : public std::exception {
 private:
  std::string err_info_;

 public:
  UnexpectedStatementException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

class VariableAlreadyDeclaredException : public std::exception {
 private:
  std::string err_info_;

 public:
  VariableAlreadyDeclaredException(std::string err_info)
      : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

class VariableDoesNotExistException : public std::exception {
 private:
  std::string err_info_;

 public:
  VariableDoesNotExistException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

#endif