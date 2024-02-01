#include <string>

#include <gtest/gtest.h>
#include "operator.hpp"
#include "token.hpp"
#include "lexer.hpp"

// TEST(Lexer, NextToken) {
//     Lexer test1 = Lexer("set hello = 2");
//     EXPECT_EQ(test1.NextToken().get(), GenerateToken("set", TokenType::SET, OperatorPtr(nullptr)).get());  
//     EXPECT_EQ(test1.NextToken().get(), GenerateToken("hello", TokenType::IDENTIFIER, OperatorPtr(nullptr)).get());  
//     EXPECT_EQ(test1.NextToken().get(), GenerateToken("=", TokenType::OPERATOR, GenerateOp("=", OperatorType::EQUAL, OpDirection::BOTH)).get());  
//     EXPECT_EQ(test1.NextToken().get(), GenerateToken("2", TokenType::INTEGER, OperatorPtr(nullptr)).get());  
//     EXPECT_EQ(test1.NextToken().get(), GenerateToken("", TokenType::EOL, OperatorPtr(nullptr)).get());  
// }