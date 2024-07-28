/**
 * @file ast.hpp
 * @brief Statement and Expression classes for the Abstract Syntax Tree (AST)
 * that can be converted from Tokens to AST nodes using the Parser.
 */
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
class NotExpression;
class BinaryExpression;
class IdentifierExpression;
class NumberExpression;
class WhitespaceExpression;
class NullExpression;

typedef std::shared_ptr<Statement> StatementPtr;
typedef std::shared_ptr<Expression> ExpressionPtr;

/**
 * @brief Enum class for the different types of Statement and Expression in the
 * AST.
 */
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
  NotExpr,
  VariableAssignExpr,
  ComparisonExpr,
  StringExpr,
};

/**
 * @brief Convert the AST NodeType enum to String that displays what type it is
 * for debugging purposes.
 * @param node_type The AST NodeType enum (It can be found in Type() method).
 * @return The string representation of the AST NodeType enum.
 */
std::string NodeEnumToString(NodeType node_type);

/**
 * @brief Base class for all Statement and Expression classes.
 */
class Statement {
 public:
  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   */
  virtual NodeType Type() const = 0;

  /**
   * @brief Virtual method to print the Statement or Expression to the output
   * stream. Making virtual operator<< is not allowed, Hence this virtual
   * function will be acting as a second layer.
   * https://stackoverflow.com/questions/4571611/making-operator-virtual
   * @param out std::ostream reference to print the Statement or Expression.
   */
  virtual void PrintOstream(std::ostream &out) const = 0;
};

/**
 * @brief Class for the Program Statement that contains a queue of Statement and
 * Expression.
 */
class Program : public Statement {
 public:
  /**
   * @brief Default constructor for the Program class.
   */
  Program() { body_ = std::queue<StatementPtr>(); }

  /**
   * @brief Constructor for the Program class that takes a queue of Statement
   * and Expression.
   * @param stmt_vec The queue of Statement and Expression.
   */
  Program(std::queue<StatementPtr> stmt_vec) : body_(stmt_vec){};

  virtual ~Program() = default;

  /**
   * @brief Queue of Statement and Expression. This is going to be used to
   * dequeue the Statement and Expression in the Runtime Evaluator.
   */
  std::queue<StatementPtr> body_;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The Program NodeType.
   */
  NodeType Type() const override { return NodeType::Program; }

  /**
   * @brief Print the Program Statement to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the Program Statement to the output
   * stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param program The Program Statement to print.
   */
  friend std::ostream &operator<<(std::ostream &out, const Program &program) {
    program.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for Expression that is a subclass of Statement. (Statement is
 * set, if, while, for, etc. and Expression is a + b, 1 + 2, etc.)
 */
class Expression : public Statement {};

/**
 * @brief Class for binary calculation expressions like a + b, a - b, a * b, a /
 * b, etc.
 */
class BinaryExpression : public Expression {
 public:
  /**
   * @brief Constructor for the BinaryExpression class
   * @param left The left Expression.
   * @param op The operator.
   * @param right The right Expression.
   */
  BinaryExpression(ExpressionPtr left, std::string op, ExpressionPtr right)
      : left_(left), right_(right), op_(op){};

  virtual ~BinaryExpression() = default;

  /**
   * @brief Left Expression.
   */
  ExpressionPtr left_;
  /**
   * @brief Right Expression.
   */
  ExpressionPtr right_;
  /**
   * @brief Operator. "+", "-", "*", "/", etc.
   */
  std::string op_;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The BinaryExpression NodeType.
   */
  NodeType Type() const override { return NodeType::BinaryExpr; }

  /**
   * @brief Print the BinaryExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the BinaryExpression to the output
   * stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param binary_expr The BinaryExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const BinaryExpression &binary_expr) {
    binary_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Identifier.
 */
class IdentifierExpression : public Expression {
 public:
  /**
   * @brief Constructor for the IdentifierExpression class that takes an
   * identifier.
   * @param identifier The identifier, the variable name.
   */
  IdentifierExpression(std::string identifier) : identifier_(identifier){};

  virtual ~IdentifierExpression() = default;

  /**
   * @brief The name of the variable.
   */
  std::string identifier_;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The IdentifierExpression NodeType.
   */
  NodeType Type() const override { return NodeType::IdentifierExpr; }

  /**
   * @brief Print the IdentifierExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the IdentifierExpression to the
   * output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param identifier_expr The IdentifierExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const IdentifierExpression &identifier_expr) {
    identifier_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Number Expression.
 */
class NumberExpression : public Expression {
 public:
  /**
   * @brief Constructor for the NumberExpression class that takes a number.
   * @param tok_value The number in double.
   */
  NumberExpression(double tok_value) : tok_value_(tok_value){};

  virtual ~NumberExpression() = default;

  /**
   * @brief The number in double.
   */
  double tok_value_;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The NumberExpression NodeType.
   */
  NodeType Type() const override { return NodeType::NumberExpr; }

  /**
   * @brief Print the NumberExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the NumberExpression to the output
   * stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param num_expr The NumberExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const NumberExpression &num_expr) {
    num_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Whitespaces.
 */
class WhitespaceExpression : public Expression {
 public:
  /**
   * @brief Constructor for the WhitespaceExpression class that takes a
   * whitespace.
   * @param tok_value The whitespace.
   */
  WhitespaceExpression(std::string tok_value) : tok_value_(tok_value){};

  virtual ~WhitespaceExpression() = default;

  /**
   * @brief The whitespace. (Can be multiple whitespaces)
   */
  std::string tok_value_;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The WhitespaceExpression NodeType.
   */
  NodeType Type() const override { return NodeType::WhitespaceExpr; }

  /**
   * @brief Print the WhitespaceExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the WhitespaceExpression to the
   * output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param whitespace_expr The WhitespaceExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const WhitespaceExpression &whitespace_expr) {
    whitespace_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Null Expression.
 */
class NullExpression : public Expression {
 public:
  /**
   * @brief Constructor for the NullExpression class.
   */
  NullExpression(){};

  virtual ~NullExpression() = default;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The NullExpression NodeType.
   */
  NodeType Type() const override { return NodeType::NullExpr; }

  /**
   * @brief Print the NullExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the NullExpression to the output
   * stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param null_expr The NullExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const NullExpression &null_expr) {
    null_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Boolean Expression.
 */
class BooleanExpression : public Expression {
 public:
  /**
   * @brief Constructor for the BooleanExpression class that takes a boolean.
   * @param boolean The boolean.
   */
  BooleanExpression(std::string boolean) : boolean_(boolean){};

  /**
   * @brief The boolean. "true" or "false".
   */
  std::string boolean_;

  virtual ~BooleanExpression() = default;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The BooleanExpression NodeType.
   */
  NodeType Type() const override { return NodeType::BooleanExpr; }

  /**
   * @brief Print the BooleanExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the BooleanExpression to the output
   * stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param bool_expr The BooleanExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const BooleanExpression &bool_expr) {
    bool_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Not (!) Expression.
 */
class NotExpression : public Expression {
 public:
  /**
   * @brief Constructor for the NotExpression class that takes an Expression to
   * negate.
   * @param expr The Expression to negate.
   */
  NotExpression(ExpressionPtr expr) : expr_(expr){};

  /**
   * @brief The Expression to negate.
   */
  ExpressionPtr expr_;

  virtual ~NotExpression() = default;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The NotExpression NodeType.
   */
  NodeType Type() const override { return NodeType::NotExpr; }

  /**
   * @brief Print the NotExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the NotExpression to the output
   * stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param not_expr The NotExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const NotExpression &not_expr) {
    not_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Variable Declaration.
 */
class VariableDeclarationStatement : public Statement {
 public:
  /**
   * @brief Constructor for the VariableDeclarationStatement class that takes an
   * identifier.
   * @param identifier The identifier of the variable.
   */
  VariableDeclarationStatement(std::string identifier) {
    identifier_ = identifier;
    value_ = ExpressionPtr(new NullExpression());
  };

  /**
   * @brief Constructor for the VariableDeclarationStatement class that takes an
   * identifier and a value (Var Declaration and Var Assignment are different,
   * Declaration is for the first time assignment, Assignment is for
   * re-assignment)
   * @param identifier The identifier of the variable.
   * @param value The value of the variable that will be assigned to the
   * identifier.
   */
  VariableDeclarationStatement(std::string identifier, ExpressionPtr value)
      : identifier_(identifier), value_(value){};

  virtual ~VariableDeclarationStatement() = default;

  /**
   * @brief The identifier of the variable.
   */
  std::string identifier_;
  /**
   * @brief The value of the variable that will be assigned to the identifier.
   */
  ExpressionPtr value_;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The VariableDeclarationStatement NodeType.
   */
  NodeType Type() const override { return NodeType::VariableDeclarationStmt; }

  /**
   * @brief Print the VariableDeclarationStatement to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the VariableDeclarationStatement to
   * the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param var_decl_stmt The VariableDeclarationStatement to print.
   */
  friend std::ostream &operator<<(
      std::ostream &out, const VariableDeclarationStatement &var_decl_stmt) {
    var_decl_stmt.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Variable Assignment.
 * (Var Declaration and Var Assignment are different, Declaration is for the
 * first time assignment, Assignment is for re-assignment)
 */
class VariableAssignExpression : public Expression {
 public:
  /**
   * @brief Constructor for the VariableAssignExpression class that takes an
   * identifier and a value.
   * @param identifier The identifier of the variable.
   * @param value The value of the variable that will be assigned to the
   * identifier.
   */
  VariableAssignExpression(std::string identifier, StatementPtr value)
      : Name(identifier), Value(value){};

  virtual ~VariableAssignExpression() = default;

  /**
   * @brief The identifier of the variable.
   */
  std::string Name;
  /**
   * @brief The value of the variable that will be assigned to the identifier.
   */
  StatementPtr Value;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The VariableAssignExpression NodeType.
   */
  NodeType Type() const override { return NodeType::VariableAssignExpr; }

  /**
   * @brief Print the VariableAssignExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the VariableAssignExpression to the
   * output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param var_assign_stmt The VariableAssignExpression to print.
   */
  friend std::ostream &operator<<(
      std::ostream &out, const VariableAssignExpression &var_assign_stmt) {
    var_assign_stmt.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the Comparison Expression.
 */
class ComparisonExpression : public Expression {
 public:
  /**
   * @brief Constructor for the ComparisonExpression class that takes a left
   * Expression, an operator, and a right Expression.
   * @param lhs The left Expression.
   * @param op The operator.
   * @param rhs The right Expression.
   */
  ComparisonExpression(ExpressionPtr lhs, std::string op, ExpressionPtr rhs)
      : left_(lhs), op_(op), right_(rhs){};

  /**
   * @brief The left Expression.
   */
  ExpressionPtr left_;
  /**
   * @brief The operator. "==" or "!="
   */
  std::string op_;
  /**
   * @brief The right Expression.
   */
  ExpressionPtr right_;

  virtual ~ComparisonExpression() = default;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The ComparisonExpression NodeType.
   */
  NodeType Type() const override { return NodeType::ComparisonExpr; }

  /**
   * @brief Print the ComparisonExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  friend std::ostream &operator<<(std::ostream &out,
                                  const ComparisonExpression &compare_expr) {
    compare_expr.PrintOstream(out);

    return out;
  }
};

/**
 * @brief Class for the String Expression.
 */
class StringExpression : public Expression {
 public:
  /**
   * @brief Constructor for the StringExpression class that takes a string.
   * @param str The string value.
   */
  StringExpression(std::string str) : tok_value_(str){};

  /**
   * @brief The string value.
   */
  std::string tok_value_;

  virtual ~StringExpression() = default;

  /**
   * @brief Type method to get the NodeType of the Statement or Expression.
   * @return The StringExpression NodeType.
   */
  NodeType Type() const override { return NodeType::StringExpr; }

  /**
   * @brief Print the StringExpression to the output stream.
   * @param out std::ostream reference to print the Statement or Expression.
   */
  void PrintOstream(std::ostream &out) const override;

  /**
   * @brief Overload the operator<< to print the StringExpression to the output
   * stream.
   * @param out std::ostream reference to print the Statement or Expression.
   * @param str_expr The StringExpression to print.
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const StringExpression &str_expr) {
    str_expr.PrintOstream(out);

    return out;
  }
};

#endif
