#include "runtime.hpp"

#include <memory>
#include <sstream>
#include <unordered_map>

Environment::Environment() {
  var_map_ = std::unordered_map<std::string, RuntimeValuePtr>();
}

void Environment::DefineVariable(std::string identifier,
                                 RuntimeValuePtr runtime_val) {
  std::unordered_map<std::string, RuntimeValuePtr>::iterator var_finder =
      var_map_.find(identifier);

  if (var_finder != var_map_.cend()) {
    std::stringstream ssVariableAlreadyDeclaredMsg;
    ssVariableAlreadyDeclaredMsg << "Variable : " << identifier
                                 << " already declared";
    throw VariableAlreadyDeclaredException(ssVariableAlreadyDeclaredMsg.str());
  }

  var_map_.insert(make_pair(identifier, runtime_val));
}

void Environment::AssignVariable(std::string identifier,
                                 RuntimeValuePtr runtime_val) {
  std::unordered_map<std::string, RuntimeValuePtr>::iterator var_finder =
      var_map_.find(identifier);

  if (var_finder == var_map_.cend()) {
    std::stringstream ss_var_not_decl_msg;
    ss_var_not_decl_msg << "Variable : " << identifier
                        << " is not declared, hence not assignable";
    throw VariableDoesNotExistException(ss_var_not_decl_msg.str());
  }

  var_map_[identifier] = runtime_val;
}

RuntimeValuePtr Environment::GetRuntimeValue(std::string name) {
  std::unordered_map<std::string, RuntimeValuePtr>::iterator var_finder =
      var_map_.find(name);
  if (var_finder == var_map_.end()) return RuntimeValuePtr(nullptr);

  return var_finder->second;
}

Evaluater::Evaluater() { env_ = Environment(); }

std::string Evaluater::EvaluateProgram(Program instructions) {
  Program program = instructions;
  RuntimeValuePtr lasteval;
  std::queue<StatementPtr> stmt_queue = program.body_;

  while (!stmt_queue.empty()) {
    lasteval = Evaluate(stmt_queue.front());
    stmt_queue.pop();
  }

  return lasteval->Value();
}

RuntimeValuePtr Evaluater::EvaluateBinaryExpression(
    BinaryExpression binary_expr) {
  RuntimeValuePtr lhs = Evaluate(binary_expr.left_);
  RuntimeValuePtr rhs = Evaluate(binary_expr.right_);

  if (lhs->Type() == ValueType::NUMBER && rhs->Type() == ValueType::NUMBER) {
    std::shared_ptr<NumberValue> lhs_number =
        std::dynamic_pointer_cast<NumberValue>(lhs);
    std::shared_ptr<NumberValue> rhs_number =
        std::dynamic_pointer_cast<NumberValue>(rhs);
    NumberValue result = EvaluateNumericBinaryExpression(
        *lhs_number, *rhs_number, binary_expr.op_);
    return std::make_unique<NumberValue>(result);
  }
  if ((lhs->Type() == ValueType::BOOLEAN || lhs->Type() == ValueType::NUMBER) &&
      (rhs->Type() == ValueType::BOOLEAN || rhs->Type() == ValueType::NUMBER)) {
    std::shared_ptr<NumberValue> lhs_number;
    std::shared_ptr<NumberValue> rhs_number;
    if (lhs->Type() == ValueType::BOOLEAN) {
      if (lhs->Value() == "true")
        lhs_number = std::make_shared<NumberValue>(1);
      else
        lhs_number = std::make_shared<NumberValue>(0);
    } else {
      std::dynamic_pointer_cast<NumberValue>(lhs);
    }

    if (rhs->Type() == ValueType::BOOLEAN) {
      if (rhs->Value() == "true")
        rhs_number = std::make_shared<NumberValue>(1);
      else
        rhs_number = std::make_shared<NumberValue>(0);
    } else {
      rhs_number = std::dynamic_pointer_cast<NumberValue>(rhs);
    }

    NumberValue result = EvaluateNumericBinaryExpression(
        *lhs_number, *rhs_number, binary_expr.op_);
    return std::make_unique<NumberValue>(result);
  }

  return std::make_unique<NullValue>();
}

NumberValue Evaluater::EvaluateNumericBinaryExpression(NumberValue lhs,
                                                       NumberValue rhs,
                                                       std::string op) {
  double result = 0;
  double lhs_val = std::stod(lhs.Value());
  double rhs_val = std::stod(rhs.Value());

  if (op == "+") {
    result = lhs_val + rhs_val;
  } else if (op == "-") {
    result = lhs_val - rhs_val;
  } else if (op == "/") {
    result = lhs_val / rhs_val;
  } else if (op == "*") {
    result = lhs_val * rhs_val;
  }
  return NumberValue(result);
}

RuntimeValuePtr Evaluater::Evaluate(StatementPtr curr_stmt) {
  RuntimeValuePtr matchValue;
  std::stringstream ss_invalid_stmt_msg;

  switch (curr_stmt->Type()) {
    case NodeType::NullExpr:
      matchValue = std::make_unique<NullValue>();
      break;
    case NodeType::NumberExpr: {
      std::shared_ptr<NumberExpression> int_expr =
          std::dynamic_pointer_cast<NumberExpression>(curr_stmt);
      if (!int_expr) {
        ss_invalid_stmt_msg
            << "Failed to cast StatementPtr to IntegerExpressionPtr : "
            << curr_stmt;
        throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      }
      matchValue = std::make_unique<NumberValue>(int_expr->tok_value_);
      break;
    }
    case NodeType::BinaryExpr: {
      std::shared_ptr<BinaryExpression> binary_expr =
          std::dynamic_pointer_cast<BinaryExpression>(curr_stmt);
      if (!binary_expr) {
        ss_invalid_stmt_msg
            << "Failed to cast StatementPtr to BinaryExpressionPtr : "
            << curr_stmt;
        throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      }
      matchValue = EvaluateBinaryExpression(*binary_expr);
      break;
    }
    case NodeType::IdentifierExpr: {
      std::shared_ptr<IdentifierExpression> identifier_expr =
          std::dynamic_pointer_cast<IdentifierExpression>(curr_stmt);
      if (!identifier_expr) {
        ss_invalid_stmt_msg
            << "Failed to cast StatementPtr to IdentifierExpressionPtr : "
            << curr_stmt;
        throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      }
      matchValue = env_.GetRuntimeValue(identifier_expr->identifier_);
      break;
    }
    case NodeType::VariableDeclarationStmt: {
      std::shared_ptr<VariableDeclarationStatement> var_decl_stmt =
          std::dynamic_pointer_cast<VariableDeclarationStatement>(curr_stmt);
      if (!var_decl_stmt) {
        ss_invalid_stmt_msg << "Failed to cast StatementPtr to "
                               "VariableDeclarationStatementPtr : "
                            << curr_stmt;
        throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      }
      matchValue = EvaluateDefiningIdentifierExpression(*var_decl_stmt);
      break;
    }
    case NodeType::VariableAssignExpr: {
      std::shared_ptr<VariableAssignExpression> var_decl_expr =
          std::dynamic_pointer_cast<VariableAssignExpression>(curr_stmt);
      if (!var_decl_expr) {
        ss_invalid_stmt_msg << "Failed to cast StatementPtr to "
                               "VariableAssignExpressionPtr : "
                            << curr_stmt;
        throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      }
      matchValue = EvaluateAssignIdentifierExpression(*var_decl_expr);
      break;
    }
    case NodeType::ComparisonExpr: {
      std::shared_ptr<ComparisonExpression> compare_expr =
          std::dynamic_pointer_cast<ComparisonExpression>(curr_stmt);
      if (!compare_expr) {
        ss_invalid_stmt_msg << "Failed to cast StatementPtr to "
                               "ComparisonExpression : "
                            << curr_stmt;
        throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      }
      matchValue = EvaluateComparisonExpression(*compare_expr);
      break;
    }
    case NodeType::BooleanExpr: {
      std::shared_ptr<BooleanExpression> bool_expr =
          std::dynamic_pointer_cast<BooleanExpression>(curr_stmt);
      if (!bool_expr) {
        ss_invalid_stmt_msg
            << "Failed to cast StatementPtr to BooleanExpression : "
            << curr_stmt;
        throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      }
      matchValue = std::make_unique<BooleanValue>(bool_expr->boolean_);
      break;
    }
    default:
      ss_invalid_stmt_msg
          << "Unimplemented Statement(Expression) in Evaluate Expression : "
          << curr_stmt;
      throw UnexpectedStatementException(ss_invalid_stmt_msg.str());
      break;
  }
  return matchValue;
}

RuntimeValuePtr Evaluater::EvaluateDefiningIdentifierExpression(
    VariableDeclarationStatement var_decl_stmt) {
  RuntimeValuePtr evalAssignedVal = Evaluate(var_decl_stmt.value_);
  env_.DefineVariable(var_decl_stmt.identifier_, evalAssignedVal);

  return evalAssignedVal;
}

RuntimeValuePtr Evaluater::EvaluateAssignIdentifierExpression(
    VariableAssignExpression var_assign_expr) {
  RuntimeValuePtr eval_assigned_val = Evaluate(var_assign_expr.Value);
  env_.AssignVariable(var_assign_expr.Name, eval_assigned_val);

  return eval_assigned_val;
}

RuntimeValuePtr Evaluater::EvaluateComparisonExpression(
    ComparisonExpression compare_expr) {
  RuntimeValuePtr lhs = Evaluate(compare_expr.left_);
  RuntimeValuePtr rhs = Evaluate(compare_expr.right_);

  bool is_equal_op = compare_expr.op_ == "==" ? true : false;

  // Compare value of equal type
  if (lhs->Type() == rhs->Type()) {
    bool is_equal_val = lhs->Value() == rhs->Value();
    std::string eval_boolean_str = is_equal_val ? "true" : "false";
    if (!is_equal_op) {
      eval_boolean_str = is_equal_val ? "false" : "true";
    }

    return std::make_shared<BooleanValue>(eval_boolean_str);
  }

  // if int > 0 then converted to true, else false
  if ((lhs->Type() == ValueType::NUMBER && rhs->Type() == ValueType::BOOLEAN) ||
      (lhs->Type() == ValueType::BOOLEAN && rhs->Type() == ValueType::NUMBER)) {
    if (lhs->Type() != ValueType::NUMBER) {
      RuntimeValuePtr temp = lhs;
      lhs = rhs;
      rhs = temp;
    }
    std::string num_to_bool = std::stoi(lhs->Value()) > 0 ? "true" : "false";
    bool is_equal_val = num_to_bool == rhs->Value();
    std::string eval_boolean_str = is_equal_val ? "true" : "false";
    if (!is_equal_op) {
      eval_boolean_str = is_equal_val ? "false" : "true";
    }

    return std::make_shared<BooleanValue>(eval_boolean_str);
  }
  return std::make_unique<BooleanValue>("false");
}
