#include <gtest/gtest.h>

#include <string>

#include "lexer.hpp"
#include "operator.hpp"
#include "token.hpp"

TEST(LexerTest, EmptyInput) {
  Lexer test1 = Lexer("");

  // 1
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr))));
}

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

  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr))));
}

TEST(LexerTest, String) {
  // "Hello \" World "
  Lexer test1 = Lexer("\"Hello \\\" World \"");

  // 1
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("Hello \" World ", TokenType::STRING,
                            OperatorPtr(nullptr))));

  // 2
  EXPECT_EQ(*(test1.NextToken()),
            *(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr))));

  // "1 - 2\"" + "\"Cool\""
  Lexer test2 = Lexer("\"1 - 2\\\" \" + \"\\\"Cool\\\"\"");

  // 1
  EXPECT_EQ(*(test2.NextToken()), *(GenerateToken("1 - 2\" ", TokenType::STRING,
                                                  OperatorPtr(nullptr))));

  // 2
  EXPECT_EQ(*(test2.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 3
  EXPECT_EQ(*(test2.NextToken()),
            *(GenerateToken("+", TokenType::OPERATOR,
                            GenerateOp("+", OperatorType::PLUS))));

  // 4
  EXPECT_EQ(*(test2.NextToken()),
            *(GenerateToken(" ", TokenType::WHITESPACE, OperatorPtr(nullptr))));

  // 5
  EXPECT_EQ(*(test2.NextToken()), *(GenerateToken("\"Cool\"", TokenType::STRING,
                                                  OperatorPtr(nullptr))));

  // 6
  EXPECT_EQ(*(test2.NextToken()),
            *(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr))));

  // "\"\"\"\"\"\""
  Lexer test3 = Lexer("\"\"\"\"\"\"");

  // 1
  EXPECT_EQ(*(test3.NextToken()),
            *(GenerateToken("", TokenType::STRING, OperatorPtr(nullptr))));

  // 2
  EXPECT_EQ(*(test3.NextToken()),
            *(GenerateToken("", TokenType::STRING, OperatorPtr(nullptr))));

  // 3
  EXPECT_EQ(*(test3.NextToken()),
            *(GenerateToken("", TokenType::STRING, OperatorPtr(nullptr))));

  // 4
  EXPECT_EQ(*(test3.NextToken()),
            *(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr))));

  // "\"😂\""
  Lexer test4 = Lexer("\"😂\"");

  // 1
  EXPECT_EQ(*(test4.NextToken()),
            *(GenerateToken("😂", TokenType::STRING, OperatorPtr(nullptr))));

  // 2
  EXPECT_EQ(*(test4.NextToken()),
            *(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr))));
}

TEST(LexerTest, IncompleteStringException) {
  // "\"Hello"
  Lexer test1 = Lexer("\"Hello");

  // 1
  EXPECT_THROW(*(test1.NextToken()), WrongLexingException);

  // "\"\\\\"Who is this\\\\""
  Lexer test2 = Lexer("\"Hello");

  // 1
  EXPECT_THROW(*(test2.NextToken()), WrongLexingException);
}