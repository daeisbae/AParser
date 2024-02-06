#include <gtest/gtest.h>

#include <string>

#include "lexer.hpp"
#include "operator.hpp"
#include "token.hpp"

TEST(Lexer, AssignIntegerToVariable) {
  Lexer test1 = Lexer("set hello = 2");

  // 1
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("set", TokenType::SET, OperatorPtr(nullptr))));

  // 2
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 3
  EXPECT_EQ(
      *(test1.NextToken()),
      *(GenerateToken("hello", TokenType::IDENTIFIER, OperatorPtr(nullptr))));

  // 4
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 5
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("=", TokenType::OPERATOR,
                            GenerateOp("=", OperatorType::EQUAL))));

  // 6
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 7
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("2", TokenType::INTEGER, OperatorPtr(nullptr))));

  // 8
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr))));
}