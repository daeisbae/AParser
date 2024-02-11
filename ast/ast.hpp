#ifndef AST_H
#define AST_H

#include <queue>
#include <string>
#include <vector>

#include "token.hpp"

class Statement;
class Program;
class Expression;

enum class NodeType {
  Program,
  IdentifierExpr,
  IntegerExpr,
  BinaryExpr,
};

typedef std::shared_ptr<Statement> StatementPtr;

typedef std::shared_ptr<Expression> ExpressionPtr;

std::string NodeEnumToString(NodeType nodetype);

class Statement {
 public:
  virtual NodeType Type() const = 0;

  // Making virtual operator<< is not allowed, Hence this virtual function will
  // be acting as a second layer.
  // https://stackoverflow.com/questions/4571611/making-operator-virtual
  virtual void PrintOstream(std::ostream& out) const = 0;
};

class Program : public Statement {
 public:
  Program() { Body = std::vector<StatementPtr>(); }

  std::vector<StatementPtr> Body;

  NodeType Type() const override { return NodeType::Program; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(std::ostream& out, const Program& program) {
    program.PrintOstream(out);

    return out;
  }
};

class Expression : public Statement {};

class BinaryExpression : public Expression {
 public:
  BinaryExpression(ExpressionPtr left, std::string op, ExpressionPtr right)
      : Left(left), Right(right), OP(op){};

  ExpressionPtr Left;
  ExpressionPtr Right;
  std::string OP;

  NodeType Type() const override { return NodeType::BinaryExpr; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(std::ostream& out,
                                  const BinaryExpression& binaryExpr) {
    binaryExpr.PrintOstream(out);

    return out;
  }
};

class IdentifierExpression : public Expression {
 public:
  IdentifierExpression(std::string name) : Name(name){};

  std::string Name;

  NodeType Type() const override { return NodeType::IdentifierExpr; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(std::ostream& out,
                                  const IdentifierExpression& identifierExpr) {
    identifierExpr.PrintOstream(out);

    return out;
  }
};

class IntegerExpression : public Expression {
 public:
  IntegerExpression(int tokValue) : Value(tokValue){};

  int Value;

  NodeType Type() const override { return NodeType::IntegerExpr; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(std::ostream& out,
                                  const IntegerExpression& integerExpr) {
    integerExpr.PrintOstream(out);

    return out;
  }
};

#endif