#ifndef AST_H
#define AST_H

#include <queue>
#include <string>

#include "token.hpp"

class Statement;
class Program;
class VariableAssignExpression;
class VariableDeclarationStatement;
class ComparisonExpression;
class Expression;
class BinaryExpression;
class IdentifierExpression;
class NumberExpression;
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
  NumberExpr,
  BinaryExpr,
  WhitespaceExpr,
  BooleanExpr,
  NullExpr,
  VariableAssignExpr,
  ComparisonExpr,
};

std::string NodeEnumToString(NodeType node_type);

class Statement {
 public:
  virtual NodeType Type() const = 0;

  // Making virtual operator<< is not allowed, Hence this virtual function will
  // be acting as a second layer.
  // https://stackoverflow.com/questions/4571611/making-operator-virtual
  virtual void PrintOstream(std::ostream &out) const = 0;
};

class Program : public Statement {
 public:
  Program() { body_ = std::queue<StatementPtr>(); }
  Program(std::queue<StatementPtr> stmt_vec) : body_(stmt_vec){};

  virtual ~Program() = default;

  std::queue<StatementPtr> body_;

  NodeType Type() const override { return NodeType::Program; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out, const Program &program) {
    program.PrintOstream(out);

    return out;
  }
};

class Expression : public Statement {};

class BinaryExpression : public Expression {
 public:
  BinaryExpression(ExpressionPtr left, std::string op, ExpressionPtr right)
      : left_(left), right_(right), op_(op){};

  virtual ~BinaryExpression() = default;

  ExpressionPtr left_;
  ExpressionPtr right_;
  std::string op_;

  NodeType Type() const override { return NodeType::BinaryExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const BinaryExpression &binary_expr) {
    binary_expr.PrintOstream(out);

    return out;
  }
};

class IdentifierExpression : public Expression {
 public:
  IdentifierExpression(std::string identifier) : identifier_(identifier){};

  virtual ~IdentifierExpression() = default;

  std::string identifier_;

  NodeType Type() const override { return NodeType::IdentifierExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const IdentifierExpression &identifier_expr) {
    identifier_expr.PrintOstream(out);

    return out;
  }
};

class NumberExpression : public Expression {
 public:
  NumberExpression(double tok_value) : tok_value_(tok_value){};

  virtual ~NumberExpression() = default;

  double tok_value_;

  NodeType Type() const override { return NodeType::NumberExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const NumberExpression &num_expr) {
    num_expr.PrintOstream(out);

    return out;
  }
};

class WhitespaceExpression : public Expression {
 public:
  WhitespaceExpression(std::string tok_value) : tok_value_(tok_value){};

  virtual ~WhitespaceExpression() = default;

  std::string tok_value_;

  NodeType Type() const override { return NodeType::WhitespaceExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const WhitespaceExpression &whitespace_expr) {
    whitespace_expr.PrintOstream(out);

    return out;
  }
};

class NullExpression : public Expression {
 public:
  NullExpression(){};

  virtual ~NullExpression() = default;

  NodeType Type() const override { return NodeType::NullExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const NullExpression &null_expr) {
    null_expr.PrintOstream(out);

    return out;
  }
};

class BooleanExpression : public Expression {
 public:
  BooleanExpression(std::string boolean) : boolean_(boolean){};

  std::string boolean_;

  virtual ~BooleanExpression() = default;

  NodeType Type() const override { return NodeType::BooleanExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const BooleanExpression &bool_expr) {
    bool_expr.PrintOstream(out);

    return out;
  }
};

class VariableDeclarationStatement : public Statement {
 public:
  VariableDeclarationStatement(std::string identifier) {
    identifier_ = identifier;
    value_ = ExpressionPtr(new NullExpression());
  };

  VariableDeclarationStatement(std::string identifier, ExpressionPtr value)
      : identifier_(identifier), value_(value){};

  virtual ~VariableDeclarationStatement() = default;

  std::string identifier_;
  ExpressionPtr value_;

  NodeType Type() const override { return NodeType::VariableDeclarationStmt; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(
      std::ostream &out, const VariableDeclarationStatement &var_decl_stmt) {
    var_decl_stmt.PrintOstream(out);

    return out;
  }
};

class VariableAssignExpression : public Expression {
 public:
  VariableAssignExpression(std::string identifier, StatementPtr value)
      : Name(identifier), Value(value){};

  virtual ~VariableAssignExpression() = default;

  std::string Name;
  StatementPtr Value;

  NodeType Type() const override { return NodeType::VariableAssignExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(
      std::ostream &out, const VariableAssignExpression &var_assign_stmt) {
    var_assign_stmt.PrintOstream(out);

    return out;
  }
};

class ComparisonExpression : public Expression {
 public:
  ComparisonExpression(ExpressionPtr lhs, std::string op, ExpressionPtr rhs)
      : left_(lhs), op_(op), right_(rhs){};

  ExpressionPtr left_;
  std::string op_;
  ExpressionPtr right_;

  virtual ~ComparisonExpression() = default;

  NodeType Type() const override { return NodeType::ComparisonExpr; }

  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const ComparisonExpression &compare_expr) {
    compare_expr.PrintOstream(out);

    return out;
  }
};

#endif
