#include "runtime.hpp"

#include <memory>
#include <sstream>
#include <unordered_map>

Environment::Environment() {
  variablemap = std::unordered_map<std::string, RuntimeValuePtr>();
}

void Environment::DefineVariable(std::string name,
                                 RuntimeValuePtr runtimeValue) {
  std::unordered_map<std::string, RuntimeValuePtr>::iterator varLocIter =
      variablemap.find(name);

  if (varLocIter != variablemap.cend()) {
    std::stringstream ssVariableAlreadyDeclaredMsg;
    ssVariableAlreadyDeclaredMsg << "Variable : " << name
                                 << " already declared";
    throw VariableAlreadyDeclaredException(ssVariableAlreadyDeclaredMsg.str());
  }

  variablemap.insert(make_pair(name, runtimeValue));
}

void Environment::AssignVariable(std::string name,
                                 RuntimeValuePtr runtimeValue) {
  std::unordered_map<std::string, RuntimeValuePtr>::iterator varLocIter =
      variablemap.find(name);

  if (varLocIter == variablemap.cend()) {
    std::stringstream ssVariableNotDeclaredMsg;
    ssVariableNotDeclaredMsg << "Variable : " << name
                             << " is not declared, hence not assignable";
    throw VariableDoesNotExistException(ssVariableNotDeclaredMsg.str());
  }

  variablemap[name] = runtimeValue;
}

RuntimeValuePtr Environment::GetRuntimeValue(std::string name) {
  std::unordered_map<std::string, RuntimeValuePtr>::iterator varLocIter =
      variablemap.find(name);
  if (varLocIter == variablemap.end()) return RuntimeValuePtr(nullptr);

  return varLocIter->second;
}

Evaluater::Evaluater() { env = Environment(); }

std::string Evaluater::EvaluateProgram(Program astProgram) {
  program = astProgram;
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
  if ((lhs->Type() == ValueType::BOOLEAN || lhs->Type() == ValueType::NUMBER) &&
      (rhs->Type() == ValueType::BOOLEAN || rhs->Type() == ValueType::NUMBER)) {
    std::shared_ptr<NumberValue> lhsNumber;
    std::shared_ptr<NumberValue> rhsNumber;
    if (lhs->Type() == ValueType::BOOLEAN) {
      if (lhs->Value() == "true")
        lhsNumber = std::make_shared<NumberValue>(1);
      else
        lhsNumber = std::make_shared<NumberValue>(0);
    } else {
      std::dynamic_pointer_cast<NumberValue>(lhs);
    }

    if (rhs->Type() == ValueType::BOOLEAN) {
      if (rhs->Value() == "true")
        rhsNumber = std::make_shared<NumberValue>(1);
      else
        rhsNumber = std::make_shared<NumberValue>(0);
    } else {
      rhsNumber = std::dynamic_pointer_cast<NumberValue>(rhs);
    }

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
    case NodeType::IdentifierExpr: {
      std::shared_ptr<IdentifierExpression> identifierExpr =
          std::dynamic_pointer_cast<IdentifierExpression>(currStmt);
      if (!identifierExpr) {
        ssInvalidStmtMsg
            << "Failed to cast StatementPtr to IdentifierExpressionPtr : "
            << currStmt;
        throw UnexpectedStatementException(ssInvalidStmtMsg.str());
      }
      matchValue = env.GetRuntimeValue(identifierExpr->Name);
      break;
    }
    case NodeType::VariableDeclarationStmt: {
      std::shared_ptr<VariableDeclarationStatement> varDeclStmt =
          std::dynamic_pointer_cast<VariableDeclarationStatement>(currStmt);
      if (!varDeclStmt) {
        ssInvalidStmtMsg << "Failed to cast StatementPtr to "
                            "VariableDeclarationStatementPtr : "
                         << currStmt;
        throw UnexpectedStatementException(ssInvalidStmtMsg.str());
      }
      matchValue = evaluateDefiningIdentifierExpression(*varDeclStmt);
      break;
    }
    case NodeType::VariableAssignExpr: {
      std::shared_ptr<VariableAssignExpression> varDeclExpr =
          std::dynamic_pointer_cast<VariableAssignExpression>(currStmt);
      if (!varDeclExpr) {
        ssInvalidStmtMsg << "Failed to cast StatementPtr to "
                            "VariableAssignExpressionPtr : "
                         << currStmt;
        throw UnexpectedStatementException(ssInvalidStmtMsg.str());
      }
      matchValue = evaluateAssignIdentifierExpression(*varDeclExpr);
      break;
    }
    case NodeType::BooleanExpr: {
      std::shared_ptr<BooleanExpression> boolExpr =
          std::dynamic_pointer_cast<BooleanExpression>(currStmt);
      if (!boolExpr) {
        ssInvalidStmtMsg
            << "Failed to cast StatementPtr to BooleanExpression : "
            << currStmt;
        throw UnexpectedStatementException(ssInvalidStmtMsg.str());
      }
      matchValue = std::make_unique<BooleanValue>(boolExpr->Value);
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

RuntimeValuePtr Evaluater::evaluateDefiningIdentifierExpression(
    VariableDeclarationStatement varDeclStmt) {
  RuntimeValuePtr evalAssignedVal = evaluate(varDeclStmt.Value);
  env.DefineVariable(varDeclStmt.Name, evalAssignedVal);

  return evalAssignedVal;
}

RuntimeValuePtr Evaluater::evaluateAssignIdentifierExpression(
    VariableAssignExpression varAssignExpr) {
  RuntimeValuePtr evalAssignedVal = evaluate(varAssignExpr.Value);
  env.AssignVariable(varAssignExpr.Name, evalAssignedVal);

  return evalAssignedVal;
}