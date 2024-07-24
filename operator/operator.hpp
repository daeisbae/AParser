/**
 * @file operator.h
 * @brief Contains the Operator class and its related functions
 */
#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Enum class to represent the type of operator
 */
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

/**
 * @brief Operator class to represent an operator in the language
 */
class Operator {
 private:
  OperatorType op_type_;
  std::string value_;
  bool overloadable_;
  int precedence_;

  // Fill out overloadable, and precedence parameter members based on
  // OperatorType member
  /**
    * @brief Fill out overloadable, and precedence parameter members based on
    * OperatorType member
    */
  void FillOperatorMembers();

 public:
  /**
   * @brief Constructor for Operator class
   * @param input The string input of the Operator
   */
  Operator(std::string input);
  /**
    * @brief Constructor for Operator class
    * @param input The string input of the Operator
    * @param op_type The operator type (OperatorType) of the Operator
    */
  Operator(std::string input, OperatorType op_type);

  ~Operator();

  /**
   * @brief Get the OperatorType of the input, since the OperatorType is in enum
   * @param input The string input of the Operator
   * @return OperatorType The OperatorType of the input
   */
  static OperatorType GetOperatorType(std::string input);

  /**
   * @brief Get the Type (OperatorType) of the Operator
   * @return OperatorType The type of the Operator
   */
  OperatorType Type() const;
  /**
   * @brief Get the string input of the Operator
   * @return std::string The string input of the Operator
   */
  std::string Text() const;
  /**
   * @brief Check if the Operator object is overloadable (ex. + operator is overloadable to ++ operator)
   * @return bool True if the Operator object is overloadable, false otherwise
   */
  bool IsOverloadable() const;
  /**
   * @brief Get the precedence of the Operator object
   * @return int The precedence of the Operator object
   */
  int Precedence() const;

  /**
   * @brief Check if the Operator object is equal to another Operator object
   * @param op The Operator object to compare with
   * @return bool True if the two Operator objects are equal, false otherwise
   */
  bool operator==(const Operator &op) const {
    return Type() == op.Type() && Text() == op.Text();
  };

  /**
    * @brief Print the Operator object for debugging purposes
    * @param out The output stream to print
    * @param op The Operator object to print
  */
  friend std::ostream &operator<<(std::ostream &out, const Operator &op) {
    out << "Operator( Value: \'" << op.value_ << "\' )";
    return out;
  };
};

/**
 * @brief Exception class for invalid OperatorType given to the Operator class
 */
class InvalidOperatorTypeException : public std::exception {
 private:
  std::string err_info_;

 public:
  InvalidOperatorTypeException(std::string err_info) : err_info_(err_info){};

  const char *what() const noexcept override { return err_info_.c_str(); }
};

typedef std::shared_ptr<Operator> OperatorPtr;

/**
 * @brief Generate an Operator object from a string input
 * @param input The string input of the Operator
 * @return OperatorPtr The Operator object generated from the input
 */
OperatorPtr GenerateOp(const std::string &input);
/**
 * @brief Generate an Operator object from a string input and OperatorType
 * @param input The string input of the Operator
 * @param op_type The OperatorType to generate the Operator object from
 * @return OperatorPtr The Operator object generated from the input
 */
OperatorPtr GenerateOp(const std::string &input, OperatorType op_type);

#endif