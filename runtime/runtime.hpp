#ifndef RUNTIME_H
#define RUNTIME_H

#include <memory>
#include <string>
#include <unordered_map>

#include "ast.hpp"

enum class ValueType { NULLABLE, NUMBER, BOOLEAN };

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
  int number_;

 public:
  NumberValue(int number) : number_(number){};

  ValueType Type() const { return ValueType::NUMBER; }
  std::string Value() const { return std::to_string(number_); }
};

class BooleanValue : public RuntimeValue {
 private:
  std::string boolean_;

 public:
  BooleanValue(std::string boolean) : boolean_(boolean){};

  ValueType Type() const { return ValueType::BOOLEAN; }
  std::string Value() const { return boolean_; }
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