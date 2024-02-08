#ifndef OPERATOR_H
#define OPERATOR_H

#include <memory>
#include <string>

enum class OperatorType {
  // General
  ASSIGN,
  INVALID,
  NOT,

  // Calculation
  PLUS,
  MINUS,
  STAR,
  SLASH,

  // Braces, Parenthesis
  L_BRACE,
  R_BRACE,
  L_PARENTHESIS,
  R_PARENTHESIS,

  // Comparison
  EQUAL,
  NOT_EQUAL,
};

class Operator {
 private:
  OperatorType optype;
  std::string value;
  bool overloadable;
  int precedence;

  // Fill out overloadable, and precedence parameter members based on
  // OperatorType member
  void fillOperatorMembers();

 public:
  Operator(std::string input);
  Operator(std::string input, OperatorType opType);
  ~Operator();

  static OperatorType GetOperatorType(std::string input);

  OperatorType Type() const;
  std::string Text() const;
  bool IsOverloadable() const;
  int Precedence() const;
};

class InvalidOperatorTypeException : public std::exception {
 private:
  std::string errinfo;

 public:
  InvalidOperatorTypeException(std::string err) : errinfo(err){};

  const char* what() const noexcept override { return errinfo.c_str(); }
};

typedef std::shared_ptr<Operator> OperatorPtr;

OperatorPtr GenerateOp(const std::string& input);
OperatorPtr GenerateOp(const std::string& input, OperatorType opType);

#endif