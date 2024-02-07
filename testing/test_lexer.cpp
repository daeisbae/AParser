#include <gtest/gtest.h>

#include <string>

#include "lexer.hpp"
#include "operator.hpp"
#include "token.hpp"

TEST(LexerTest, AssignIntegerToVariable) {
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

TEST(LexerTest, Function) {
  Lexer test1 = Lexer("set var1 = func(){ return 123 }");

  // 1
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("set", TokenType::SET, OperatorPtr(nullptr))));

  // 2
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 3
  EXPECT_EQ(*(test1.NextToken()), *(GenerateToken("var1", TokenType::IDENTIFIER,
                                                  OperatorPtr(nullptr))));

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
  EXPECT_EQ(*(test1.NextToken()), *(GenerateToken("func", TokenType::FUNCTION,
                                                  OperatorPtr(nullptr))));

  // 8
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("(", TokenType::OPERATOR,
                            GenerateOp("(", OperatorType::L_PARENTHESIS))));

  // 9
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(")", TokenType::OPERATOR,
                            GenerateOp(")", OperatorType::R_PARENTHESIS))));

  // 10
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("{", TokenType::OPERATOR,
                            GenerateOp(")", OperatorType::L_BRACE))));

  // 11
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 12
  EXPECT_EQ(*(test1.NextToken()), *(GenerateToken("return", TokenType::RETURN,
                                                  OperatorPtr(nullptr))));

  // 13
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 14
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("123", TokenType::INTEGER, OperatorPtr(nullptr))));

  // 15
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 16
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("}", TokenType::OPERATOR,
                            GenerateOp("}", OperatorType::R_BRACE))));
}