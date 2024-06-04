#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
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
  OperatorType op_type_;
  std::string value_;
  bool overloadable_;
  int precedence_;

  // Fill out overloadable, and precedence parameter members based on
  // OperatorType member
  void FillOperatorMembers();

 public:
  Operator(std::string input);
  Operator(std::string input, OperatorType op_type);
  ~Operator();

  static OperatorType GetOperatorType(std::string input);

  OperatorType Type() const;
  std::string Text() const;
  bool IsOverloadable() const;
  int Precedence() const;

  bool operator==(const Operator &op) const {
    return Type() == op.Type() && Text() == op.Text();
  };

  friend std::ostream &operator<<(std::ostream &out, const Operator &op) {
    out << "Operator( Value: \'" << op.value_ << "\' )";
    return out;
  };
};

class InvalidOperatorTypeException : public std::exception {
 private:
  std::string err_info_;

 public:
  InvalidOperatorTypeException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

typedef std::shared_ptr<Operator> OperatorPtr;

OperatorPtr GenerateOp(const std::string &input);
OperatorPtr GenerateOp(const std::string &input, OperatorType op_type);

#endif