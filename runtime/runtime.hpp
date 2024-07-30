/**
 * @file runtime.hpp
 * @brief Contains the Runtime classes for Interpreter, RuntimeValue (Value
 * Type), and Environment (For storing variables and their values)
 */
#ifndef RUNTIME_H
#define RUNTIME_H

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "ast.hpp"

/**
 * @brief The ValueType enum class for RuntimeValue Type Identifications
 */
enum class ValueType { NULLABLE, NUMBER, BOOLEAN, STRING };

/**
 * @brief The RuntimeValue class is the base class for all the value types
 * (String, Number, Boolean, Null)
 */
class RuntimeValue {
 public:
  /**
   * @brief Type returns the ValueType of the RuntimeValue
   * @return ValueType The type of the RuntimeValue
   */
  virtual ValueType Type() const = 0;
  /**
   * @brief Value returns the string representation of the RuntimeValue
   * @return std::string The value as in string format
   */
  virtual std::string Value() const = 0;
  /**
   * @brief PrintOstream prints the value to the output stream
   * @param out The output stream to print the value
   */
  void PrintOstream(std::ostream &out) const { out << Value(); }
};

/**
 * @brief The NullValue class is a subclass of RuntimeValue for representing
 * null values
 */
class NullValue : public RuntimeValue {
 public:
  /**
   * @brief NullValue Constructor for the NullValue
   */
  NullValue(){};

  /**
   * @brief Type returns the ValueType of the NullValue
   * @return ValueType::NULLABLE
   */
  ValueType Type() const { return ValueType::NULLABLE; }

  /**
   * @brief Value returns the string representation of the NullValue
   * @return std::string "null"
   */
  std::string Value() const { return "null"; }
};

/**
 * @brief The NumberValue class is a subclass of RuntimeValue for representing
 * number values
 */
class NumberValue : public RuntimeValue {
 private:
  double number_;

 public:
  /**
   * @brief NumberValue Constructor for the NumberValue
   * @param number The number to store in the NumberValue
   */
  NumberValue(double number) : number_(number){};

  /**
   * @brief Type returns the ValueType of the NumberValue
   * @return ValueType ValueType::NUMBER
   */
  ValueType Type() const { return ValueType::NUMBER; }
  /**
   * @brief Value returns the string representation of the NumberValue
   * If the number is an integer, it will format printing as an integer
   * @return std::string The number as a string
   */
  std::string Value() const { return MaxDecimalNumberInStr(); }

 private:
  // Return the number until the longest decimal point available
  /**
   * @brief MaxDecimalNumberInStr Returns the number in string format
   * with the maximum useful decimal points
   * @return std::string The number in string format with the maximum
   * useful decimal points
   */
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

/**
 * @brief The BooleanValue class is a subclass of RuntimeValue for representing
 * boolean values
 */
class BooleanValue : public RuntimeValue {
 private:
  std::string boolean_;

 public:
  /**
   * @brief BooleanValue Constructor for the BooleanValue
   * @param std::string The boolean value to store in the BooleanValue
   */
  BooleanValue(std::string boolean) : boolean_(boolean){};

  /**
   * @brief Type returns the ValueType of the BooleanValue
   * @return ValueType ValueType::BOOLEAN
   */
  ValueType Type() const { return ValueType::BOOLEAN; }

  /**
   * @brief returns the string representation of the BooleanValue
   * @return std::string The boolean value as a string
   */
  std::string Value() const { return boolean_; }
};

/**
 * @brief The StringValue class is a subclass of RuntimeValue for representing
 * string values
 */
class StringValue : public RuntimeValue {
 private:
  std::string string_;

 public:
  /**
   * @brief StringValue Constructor for the StringValue
   * @param string The string to store in the StringValue
   */
  StringValue(std::string string) : string_(string){};

  /**
   * @brief Type returns the ValueType of the StringValue
   * @return ValueType ValueType::STRING
   */
  ValueType Type() const { return ValueType::STRING; }

  /**
   * @brief Value returns the string representation of the StringValue
   * @return std::string The string value
   */
  std::string Value() const { return string_; }
};

typedef std::shared_ptr<RuntimeValue> RuntimeValuePtr;

/**
 * @brief The Environment class is the class that stores the variables values
 */
class Environment {
 private:
  std::unordered_map<std::string, RuntimeValuePtr> var_map_;

 public:
  /**
   * @brief Environment Constructor for the Environment
   */
  Environment();

  /**
   * @brief Defines a variable in the environment
   * @pre The variable should not be defined before
   * @param name The name of the variable
   * @param runtimeValue The value of the variable
   */
  void DefineVariable(std::string name, RuntimeValuePtr runtimeValue);
  /**
   * @brief Assigns a value to a variable in the environment
   * @pre The variable should be defined before
   * @param name The name of the variable
   * @param runtimeValue The value of the variable
   */
  void AssignVariable(std::string name, RuntimeValuePtr runtimeValue);
  /**
   * @brief Get the value of a variable in the environment
   * @param name The name of the variable
   * @return RuntimeValuePtr The value of the variable
   */
  RuntimeValuePtr GetRuntimeValue(std::string name);
};

/**
 * @brief The Evaluater class is the class that evaluates the AST and interprete
 * (returns) the result
 */
class Evaluater {
 private:
  Program instructions_;
  Environment env_;

  /**
   * @brief EvaluateNotExpression Evaluates the NotExpression and
   * converts the AST expression to opposite value
   * @param not_expr The NotExpression to evaluate
   * @return RuntimeValuePtr return the opposite value of the expression
   */
  RuntimeValuePtr EvaluateNotExpression(NotExpression not_expr);
  /**
   * @brief EvaluateBinaryExpression Evaluates the BinaryExpression and
   * Add/Subtract/Multiply/Divide the two expressions
   * @param bin_expr The BinaryExpression to evaluate
   * @return RuntimeValuePtr The result of the BinaryExpression in
   * Boolean/Number/Null format
   */
  RuntimeValuePtr EvaluateBinaryExpression(BinaryExpression bin_expr);
  /**
   * @brief EvaluateNumericBinaryExpression Evaluates the BinaryExpression and
   * Add/Subtract/Multiply/Divide the two expressions
   * @param lhs The left hand side of the expression
   * @param rhs The right hand side of the expression
   * @param op The operator to apply to the two expressions
   * @return NumberValue The result of the BinaryExpression in Number format
   */
  NumberValue EvaluateNumericBinaryExpression(NumberValue lhs, NumberValue rhs,
                                              std::string op);
  /**
   * @brief EvaluateDefiningIdentifierExpression Evaluates the
   * VariableDeclarationStatement and defines the variable in the environment
   * (if not already defined)
   * @pre The variable should not be defined in the environment
   * @param varDeclStmt The VariableDeclarationStatement to evaluate
   * @return RuntimeValuePtr The variable value in the environment
   */
  RuntimeValuePtr EvaluateDefiningIdentifierExpression(
      VariableDeclarationStatement varDeclStmt);
  /**
   * @brief EvaluateAssignIdentifierExpression Evaluates the
   * VariableAssignExpression and assigns the variable in the environment (it
   * should be already defined)
   * @pre The variable should be defined in the environment
   * @param varAssignExpr The VariableAssignExpression to evaluate
   * @return RuntimeValuePtr The variable value in the environment
   */
  RuntimeValuePtr EvaluateAssignIdentifierExpression(
      VariableAssignExpression varAssignExpr);
  /**
   * @brief EvaluateComparisonExpression Evaluates the ComparisonExpression
   * and compares the two expressions
   * @param compareExpr The ComparisonExpression to evaluate
   * @return RuntimeValuePtr Whether the value is same or not (In boolean)
   */
  RuntimeValuePtr EvaluateComparisonExpression(
      ComparisonExpression compareExpr);
  RuntimeValuePtr Evaluate(StatementPtr currStmt);

 public:
  /**
   * @brief Evaluater Constructor for the Evaluater
   */
  Evaluater();

  /**
   * @brief EvaluateProgram Evaluates the program and returns the result
   * @param instructions The program (Queue of Statements) to evaluate
   * @return std::string The result of the program in string format
   */
  std::string EvaluateProgram(Program instructions);
};

/**
 * @brief The UnexpectedStatementException class is an exception class for
 * undefined Statements which can't be evaluated
 * (The interpretation instruction is not defined yet)
 */
class UnexpectedStatementException : public std::exception {
 private:
  std::string err_info_;

 public:
  UnexpectedStatementException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

/**
 * @brief The VariableAlreadyDeclaredException class is an exception class
 * when the variable is already declared but tries to declare again
 */
class VariableAlreadyDeclaredException : public std::exception {
 private:
  std::string err_info_;

 public:
  VariableAlreadyDeclaredException(std::string err_info)
      : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

/**
 * @brief The VariableDoesNotExistException class is an exception class
 * when the variable is not declared but tries to assign the value
 */
class VariableDoesNotExistException : public std::exception {
 private:
  std::string err_info_;

 public:
  VariableDoesNotExistException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

#endif
