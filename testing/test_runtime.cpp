#include <gtest/gtest.h>

#include <memory>

#include "runtime.hpp"

TEST(EvaluaterTest, IntegerEvaluation) {
  std::queue<StatementPtr> stmtqueue;
  stmtqueue.push(std::make_shared<IntegerExpression>(1));

  Evaluater test1 = Evaluater();
  std::string test1Result = test1.EvaluateProgram(stmtqueue);

  // 1
  EXPECT_EQ(test1Result, "1");
}

TEST(EvaluaterTest, BooleanEvaluation) {
  {
    std::queue<StatementPtr> stmtqueue1;
    stmtqueue1.push(std::make_shared<BooleanExpression>("true"));

    Evaluater test1 = Evaluater();
    std::string test1Result = test1.EvaluateProgram(stmtqueue1);

    // 1
    EXPECT_EQ(test1Result, "true");
  }
  {
    std::queue<StatementPtr> stmtqueue2;
    stmtqueue2.push(std::make_shared<BooleanExpression>("false"));

    Evaluater test2 = Evaluater();
    std::string test2Result = test2.EvaluateProgram(stmtqueue2);

    // 2
    EXPECT_EQ(test2Result, "false");
  }
}

TEST(EvaluaterTest, NullEvaluation) {
  std::queue<StatementPtr> stmtqueue;
  stmtqueue.push(std::make_shared<NullExpression>());

  Evaluater test1 = Evaluater();
  std::string test1Result = test1.EvaluateProgram(stmtqueue);

  // 1
  EXPECT_EQ(test1Result, "null");
}

TEST(EvaluaterTest, BinaryExpression) {
  {
    std::queue<StatementPtr> stmtqueue;
    // 1 + 2
    stmtqueue.push(std::make_shared<BinaryExpression>(
        std::make_shared<IntegerExpression>(1), "+",
        std::make_shared<IntegerExpression>(2)));

    Evaluater test1 = Evaluater();
    std::string test1Result = test1.EvaluateProgram(stmtqueue);

    // 1
    EXPECT_EQ(test1Result, "3");
  }
  {
    std::queue<StatementPtr> stmtqueue2;
    // 0 - 2
    stmtqueue2.push(std::make_shared<BinaryExpression>(
        std::make_shared<IntegerExpression>(0), "-",
        std::make_shared<IntegerExpression>(2)));

    Evaluater test2 = Evaluater();
    std::string test2Result = test2.EvaluateProgram(stmtqueue2);

    // 2
    EXPECT_EQ(test2Result, "-2");
  }
  {
    std::queue<StatementPtr> stmtqueue3;
    // 3 * ( 3 + 2 )
    stmtqueue3.push(std::make_shared<BinaryExpression>(
        std::make_shared<IntegerExpression>(3), "*",
        std::make_shared<BinaryExpression>(
            std::make_shared<IntegerExpression>(3), "+",
            std::make_shared<IntegerExpression>(2))));

    Evaluater test3 = Evaluater();
    std::string test3Result = test3.EvaluateProgram(stmtqueue3);

    // 3
    EXPECT_EQ(test3Result, "15");
  }
  {
    std::queue<StatementPtr> stmtqueue4;
    // 4 - ( 3 + null )
    stmtqueue4.push(std::make_shared<BinaryExpression>(
        std::make_shared<IntegerExpression>(4), "-",
        std::make_shared<BinaryExpression>(
            std::make_shared<IntegerExpression>(3), "+",
            std::make_shared<NullExpression>())));

    Evaluater test4 = Evaluater();
    std::string test4Result = test4.EvaluateProgram(stmtqueue4);

    // 4
    EXPECT_EQ(test4Result, "null");
  }
  {
    std::queue<StatementPtr> stmtqueue5;
    // null - null
    stmtqueue5.push(std::make_shared<BinaryExpression>(
        std::make_shared<NullExpression>(), "-",
        std::make_shared<NullExpression>()));

    Evaluater test5 = Evaluater();
    std::string test5Result = test5.EvaluateProgram(stmtqueue5);

    // 5
    EXPECT_EQ(test5Result, "null");
  }
  {
    std::queue<StatementPtr> stmtqueue6;
    // true + true
    stmtqueue6.push(std::make_shared<BinaryExpression>(
        std::make_shared<BooleanExpression>("true"), "+",
        std::make_shared<BooleanExpression>("true")));

    Evaluater test6 = Evaluater();
    std::string test6Result = test6.EvaluateProgram(stmtqueue6);

    // 6
    EXPECT_EQ(test6Result, "2");
  }
  {
    std::queue<StatementPtr> stmtqueue7;
    // true - false
    stmtqueue7.push(std::make_shared<BinaryExpression>(
        std::make_shared<BooleanExpression>("true"), "-",
        std::make_shared<BooleanExpression>("false")));

    Evaluater test7 = Evaluater();
    std::string test7Result = test7.EvaluateProgram(stmtqueue7);

    // 7
    EXPECT_EQ(test7Result, "1");
  }
  {
    std::queue<StatementPtr> stmtqueue8;
    // true - false
    stmtqueue8.push(std::make_shared<BinaryExpression>(
        std::make_shared<BooleanExpression>("true"), "*",
        std::make_shared<BooleanExpression>("true")));

    Evaluater test8 = Evaluater();
    std::string test8Result = test8.EvaluateProgram(stmtqueue8);

    // 8
    EXPECT_EQ(test8Result, "1");
  }
  {
    std::queue<StatementPtr> stmtqueue9;
    // true + 10
    stmtqueue9.push(std::make_shared<BinaryExpression>(
        std::make_shared<BooleanExpression>("true"), "+",
        std::make_shared<IntegerExpression>(10)));

    Evaluater test9 = Evaluater();
    std::string test9Result = test9.EvaluateProgram(stmtqueue9);

    // 9
    EXPECT_EQ(test9Result, "11");
  }
  {
    std::queue<StatementPtr> stmtqueue10;
    // false / 1
    stmtqueue10.push(std::make_shared<BinaryExpression>(
        std::make_shared<BooleanExpression>("false"), "/",
        std::make_shared<IntegerExpression>(1)));

    Evaluater test10 = Evaluater();
    std::string test10Result = test10.EvaluateProgram(stmtqueue10);

    // 10
    EXPECT_EQ(test10Result, "0");
  }
}

TEST(EvaluaterTest, VariableDeclaration) {
  {
    std::queue<StatementPtr> stmtqueue;
    // set hello = 1
    // hello
    stmtqueue.push(std::make_shared<VariableDeclarationStatement>(
        "hello", std::make_shared<IntegerExpression>(1)));
    stmtqueue.push(std::make_shared<IdentifierExpression>("hello"));

    Evaluater test1 = Evaluater();
    std::string test1Result = test1.EvaluateProgram(stmtqueue);

    // 1
    EXPECT_EQ(test1Result, "1");
  }
  {
    std::queue<StatementPtr> stmtqueue2;
    // set var1
    // var1
    stmtqueue2.push(std::make_shared<VariableDeclarationStatement>("var1"));
    stmtqueue2.push(std::make_shared<IdentifierExpression>("var1"));

    Evaluater test2 = Evaluater();
    std::string test2Result = test2.EvaluateProgram(stmtqueue2);

    // 2
    EXPECT_EQ(test2Result, "null");
  }
  {
    std::queue<StatementPtr> stmtqueue3;
    // set testingVar = true
    // testingVar
    stmtqueue3.push(std::make_shared<VariableDeclarationStatement>(
        "testingVar", std::make_shared<BooleanExpression>("true")));
    stmtqueue3.push(std::make_shared<IdentifierExpression>("testingVar"));

    Evaluater test3 = Evaluater();
    std::string test3Result = test3.EvaluateProgram(stmtqueue3);

    // 3
    EXPECT_EQ(test3Result, "true");
  }
}

TEST(EvaluaterTest, VariableAssignment) {
  {
    std::queue<StatementPtr> stmtqueue;
    // set hello = 1
    // hello = 321
    // hello
    stmtqueue.push(std::make_shared<VariableDeclarationStatement>(
        "hello", std::make_shared<IntegerExpression>(1)));
    stmtqueue.push(std::make_shared<VariableAssignExpression>(
        "hello", std::make_shared<IntegerExpression>(321)));
    stmtqueue.push(std::make_shared<IdentifierExpression>("hello"));

    Evaluater test1 = Evaluater();
    std::string test1Result = test1.EvaluateProgram(stmtqueue);

    // 1
    EXPECT_EQ(test1Result, "321");
  }
  {
    std::queue<StatementPtr> stmtqueue2;
    // set var1
    // var1 = null
    // var1
    stmtqueue2.push(std::make_shared<VariableDeclarationStatement>("var1"));
    stmtqueue2.push(std::make_shared<VariableAssignExpression>(
        "var1", std::make_shared<NullExpression>()));
    stmtqueue2.push(std::make_shared<IdentifierExpression>("var1"));

    Evaluater test2 = Evaluater();
    std::string test2Result = test2.EvaluateProgram(stmtqueue2);

    // 2
    EXPECT_EQ(test2Result, "null");
  }
  {
    std::queue<StatementPtr> stmtqueue3;
    // set testingVar = true
    // set testingVar2 = false
    // set testingVar3 = 123
    // testingVar2 = 521
    // set testingVar4 = null
    // testingVar2
    stmtqueue3.push(std::make_shared<VariableDeclarationStatement>(
        "testingVar", std::make_shared<BooleanExpression>("true")));
    stmtqueue3.push(std::make_shared<VariableDeclarationStatement>(
        "testingVar2", std::make_shared<BooleanExpression>("false")));
    stmtqueue3.push(std::make_shared<VariableDeclarationStatement>(
        "testingVar3", std::make_shared<IntegerExpression>(123)));
    stmtqueue3.push(std::make_shared<VariableAssignExpression>(
        "testingVar2", std::make_shared<IntegerExpression>(521)));
    stmtqueue3.push(std::make_shared<VariableDeclarationStatement>(
        "testingVar4", std::make_shared<NullExpression>()));
    stmtqueue3.push(std::make_shared<IdentifierExpression>("testingVar2"));

    Evaluater test3 = Evaluater();
    std::string test3Result = test3.EvaluateProgram(stmtqueue3);

    // 3
    EXPECT_EQ(test3Result, "521");
  }
}