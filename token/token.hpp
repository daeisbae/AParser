/**
 * @file token.hpp
 * @brief Contains the Token class and Token related classes and functions
 */
#ifndef TOKEN_H
#define TOKEN_H

#include <memory>
#include <string>

#include "file.hpp"
#include "operator.hpp"

/**
 * @brief Enum class to represent different token types.
 */
enum class TokenType {
  EOL,
  INVALID,
  IDENTIFIER,
  WHITESPACE,
  SET,
  NUMBER,
  STRING,
  TRUE,
  FALSE,
  IF,
  FOR,
  FUNCTION,
  RETURN,
  OPERATOR,
  NULLABLE
};

/**
 * @brief Token class used to represent a token in the lexer
 */
class Token {
 private:
  TokenType tok_type_;
  std::string value_;
  OperatorPtr op_;

 public:
  /**
   * @brief Constructor for Token class
   * @param input The value of the token
   * @param tok_type The type of the token
   * @param op The operator associated with the token (if not, nullptr)
   */
  Token(const std::string &input, TokenType tok_type, OperatorPtr op);
  ~Token();

  /**
   * @brief Get the type of the token
   * @return TokenType of the token
   */
  TokenType Type() const;

  /**
   * @brief Get the value of the token
   * @return Value of the token
   */
  std::string Text() const;

  /**
   * @brief Get the operator associated with the token (if not, nullptr)
   * @return Operator's smart pointer of the token, since the token contains
   * operator (return nullptr if not associated with an operator)
   */
  OperatorPtr OpPtr() const;

  /**
   * @brief Print the token type as a string
   * @param tok_type The token type to check what the value is in string form
   * @return The token type as a string
   */
  static std::string PrintTokenType(TokenType tok_type);

  /**
   * @brief Check if the token is equal to another token
   * @param token The token to compare to
   * @return True if the tokens are equal, false otherwise
   */
  bool operator==(const Token &token) const {
    return Type() == token.Type() && Text() == token.Text();
  };

  /**
   * @brief Print the token as a string for debugging purposes
   * @param out The output stream to print to
   * @param token The token to print
   * @return The output stream with the token printed
   */
  friend std::ostream &operator<<(std::ostream &out, const Token &token) {
    out << "Token( TokenType: " << PrintTokenType(token.Type()) << " Value: \'"
        << token.value_ << "\' )";
    return out;
  }
};

typedef std::shared_ptr<Token> TokenPtr;

/**
 * @brief Generate a smart pointer token object based on the input, token type,
 * and operator
 * @param input The value of the token
 * @param tok_type The type of the token
 * @param op The operator associated with the token (if not, nullptr)
 * @return Token shared pointer of the generated token
 */
TokenPtr GenerateToken(const std::string &input, TokenType tok_type,
                       OperatorPtr op);

#endif
