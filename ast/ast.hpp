#ifndef AST_H
#define AST_H

#include <queue>
#include <string>

#include "token.hpp"

class Statement;
class Program;
class VariableAssignExpression;
class VariableDeclarationStatement;
class Expression;
class BinaryExpression;
class IdentifierExpression;
class IntegerExpression;
class WhitespaceExpression;
class NullExpression;

typedef std::shared_ptr<Statement> StatementPtr;
typedef std::shared_ptr<Expression> ExpressionPtr;

enum class NodeType {
  // Statement
  Program,
  VariableDeclarationStmt,

  // Expression
  IdentifierExpr,
  IntegerExpr,
  BinaryExpr,
  WhitespaceExpr,
  NullExpr,
  VariableAssignExpr,
};

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
  Program() { Body = std::queue<StatementPtr>(); }
  Program(std::queue<StatementPtr> stmtVec) : Body(stmtVec){};

  std::queue<StatementPtr> Body;

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

class WhitespaceExpression : public Expression {
 public:
  WhitespaceExpression(std::string tokValue) : Value(tokValue){};

  std::string Value;

  NodeType Type() const override { return NodeType::WhitespaceExpr; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(std::ostream& out,
                                  const WhitespaceExpression& whitespaceExpr) {
    whitespaceExpr.PrintOstream(out);

    return out;
  }
};

class NullExpression : public Expression {
 public:
  NullExpression(){};

  NodeType Type() const override { return NodeType::NullExpr; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(std::ostream& out,
                                  const NullExpression& nullExpr) {
    nullExpr.PrintOstream(out);

    return out;
  }
};

class VariableDeclarationStatement : public Statement {
 public:
  VariableDeclarationStatement(std::string identifier) {
    Name = identifier;
    Value = ExpressionPtr(new NullExpression());
  };

  VariableDeclarationStatement(std::string identifier, ExpressionPtr value)
      : Name(identifier), Value(value){};

  std::string Name;
  ExpressionPtr Value;

  NodeType Type() const override { return NodeType::VariableDeclarationStmt; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(
      std::ostream& out, const VariableDeclarationStatement& varDeclStmt) {
    varDeclStmt.PrintOstream(out);

    return out;
  }
};

class VariableAssignExpression : public Expression {
 public:
  VariableAssignExpression(std::string identifier, StatementPtr value)
      : Name(identifier), Value(value){};

  std::string Name;
  StatementPtr Value;

  NodeType Type() const override { return NodeType::VariableAssignExpr; }

  void PrintOstream(std::ostream& out) const;

  friend std::ostream& operator<<(
      std::ostream& out, const VariableAssignExpression& varAssignStmt) {
    varAssignStmt.PrintOstream(out);

    return out;
  }
};

#endif