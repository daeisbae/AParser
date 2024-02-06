#ifndef OPERATOR_H
#define OPERATOR_H

#include <memory>
#include <string>

enum class OperatorType {
  // General
  ASSIGN,
  INVALID,

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

  OperatorType Type() const;
  std::string Text() const;
  bool IsOverloadable() const;
  int Precedence() const;
};

typedef std::shared_ptr<Operator> OperatorPtr;

OperatorPtr GenerateOp(const std::string& input);
OperatorPtr GenerateOp(const std::string& input, OperatorType opType);

#endif