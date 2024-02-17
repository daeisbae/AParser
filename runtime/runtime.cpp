#include "runtime.hpp"

#include <sstream>

Evaluater::Evaluater(Program astProgram) : program(astProgram) {}

std::string Evaluater::EvaluateProgram() {
  RuntimeValuePtr lasteval;
  std::queue<StatementPtr> stmtqueue = program.Body;

  while (!stmtqueue.empty()) {
    lasteval = evaluate(stmtqueue.front());
    stmtqueue.pop();
  }

  return lasteval->Value();
}

RuntimeValuePtr Evaluater::evaluateBinaryExpression(
    BinaryExpression binaryExpr) {
  RuntimeValuePtr lhs = evaluate(binaryExpr.Left);
  RuntimeValuePtr rhs = evaluate(binaryExpr.Right);

  if (lhs->Type() == ValueType::NUMBER && rhs->Type() == ValueType::NUMBER) {
    std::shared_ptr<NumberValue> lhsNumber =
        std::dynamic_pointer_cast<NumberValue>(lhs);
    std::shared_ptr<NumberValue> rhsNumber =
        std::dynamic_pointer_cast<NumberValue>(rhs);
    NumberValue result =
        evaluateNumericBinaryExpression(*lhsNumber, *rhsNumber, binaryExpr.OP);
    return std::make_unique<NumberValue>(result);
  }

  return std::make_unique<NullValue>();
}

NumberValue Evaluater::evaluateNumericBinaryExpression(NumberValue lfs,
                                                       NumberValue rhs,
                                                       std::string op) {
  int result = 0;
  int lfsVal = std::stoi(lfs.Value());
  int rhsVal = std::stoi(rhs.Value());

  if (op == "+") {
    result = lfsVal + rhsVal;
  } else if (op == "-") {
    result = lfsVal - rhsVal;
  } else if (op == "/") {
    result = lfsVal / rhsVal;
  } else if (op == "*") {
    result = lfsVal * rhsVal;
  }
  return NumberValue(result);
}

RuntimeValuePtr Evaluater::evaluate(StatementPtr currStmt) {
  RuntimeValuePtr matchValue;
  std::stringstream ssInvalidStmtMsg;

  switch (currStmt->Type()) {
    case NodeType::NullExpr:
      matchValue = std::make_unique<NullValue>();
      break;
    case NodeType::IntegerExpr: {
      std::shared_ptr<IntegerExpression> integerExpr =
          std::dynamic_pointer_cast<IntegerExpression>(currStmt);
      if (!integerExpr) {
        ssInvalidStmtMsg
            << "Failed to cast StatementPtr to IntegerExpressionPtr : "
            << currStmt;
        throw UnexpectedStatementException(ssInvalidStmtMsg.str());
      }
      matchValue = std::make_unique<NumberValue>(integerExpr->Value);
      break;
    }
    case NodeType::BinaryExpr: {
      std::shared_ptr<BinaryExpression> binaryExpr =
          std::dynamic_pointer_cast<BinaryExpression>(currStmt);
      if (!binaryExpr) {
        ssInvalidStmtMsg
            << "Failed to cast StatementPtr to BinaryExpressionPtr : "
            << currStmt;
        throw UnexpectedStatementException(ssInvalidStmtMsg.str());
      }
      matchValue = evaluateBinaryExpression(*binaryExpr);
      break;
    }
    default:
      ssInvalidStmtMsg
          << "Unimplemented Statement(Expression) in Evaluate Expression : "
          << currStmt;
      throw UnexpectedStatementException(ssInvalidStmtMsg.str());
      break;
  }
  return matchValue;
}