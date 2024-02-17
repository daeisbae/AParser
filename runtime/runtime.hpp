#ifndef RUNTIME_H
#define RUNTIME_H

#include <memory>
#include <string>

#include "ast.hpp"

enum class ValueType {
  NULLABLE,
  NUMBER,
};

class RuntimeValue {
 public:
  virtual ValueType Type() const = 0;
  virtual std::string Value() const = 0;
  void PrintOstream(std::ostream& out) const { out << Value(); }
};

class NullValue : public RuntimeValue {
 public:
  NullValue(){};

  ValueType Type() const { return ValueType::NULLABLE; }
  std::string Value() const { return "null"; }
};

class NumberValue : public RuntimeValue {
 private:
  int value;

 public:
  NumberValue(int number) : value(number){};

  ValueType Type() const { return ValueType::NUMBER; }
  std::string Value() const { return std::to_string(value); }
};

typedef std::shared_ptr<RuntimeValue> RuntimeValuePtr;

class Evaluater {
 private:
  Program program;

  RuntimeValuePtr evaluateBinaryExpression(BinaryExpression binExpr);
  NumberValue evaluateNumericBinaryExpression(NumberValue lfs, NumberValue rhs,
                                              std::string op);
  RuntimeValuePtr evaluate(StatementPtr currStmt);

 public:
  Evaluater(Program astProgram);

  std::string EvaluateProgram();
};

class UnexpectedStatementException : public std::exception {
 private:
  std::string errinfo;

 public:
  UnexpectedStatementException(std::string err) : errinfo(err){};

  const char* what() const noexcept override { return errinfo.c_str(); }
};

#endif