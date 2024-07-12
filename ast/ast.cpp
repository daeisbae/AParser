#include "ast.hpp"

std::string NodeEnumToString(NodeType node_type) {
  std::string type_str;

  switch (node_type) {
    case NodeType::Program:
      type_str = "ProgramStatement";
      break;
    case NodeType::VariableDeclarationStmt:
      type_str = "VariableDeclarationStatement";
      break;
    case NodeType::VariableAssignExpr:
      type_str = "VariableAssignStatement";
      break;
    case NodeType::ComparisonExpr:
      type_str = "ComparisonExpression";
      break;
    case NodeType::IdentifierExpr:
      type_str = "IdentifierExpression";
      break;
    case NodeType::NumberExpr:
      type_str = "NumberExpression";
      break;
    case NodeType::BinaryExpr:
      type_str = "BinaryExpression";
      break;
    case NodeType::WhitespaceExpr:
      type_str = "WhitespaceExpression";
      break;
    case NodeType::NullExpr:
      type_str = "NullExpression";
      break;
    case NodeType::BooleanExpr:
      type_str = "BooleanExpression";
      break;
    default:
      type_str = "InvalidExpression";
      break;
  }
  return type_str;
}

void Program::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " {\n";

  std::queue<StatementPtr> program_instructions = body_;

  while (!program_instructions.empty()) {
    StatementPtr statement = program_instructions.front();
    program_instructions.pop();
    statement->PrintOstream(out);
    out << "\n";
  }

  out << "}";
}

void VariableDeclarationStatement::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Identifier : " << identifier_;
  out << ", ";
  out << "Value : ";
  value_->PrintOstream(out);

  out << " )";
}

void VariableAssignExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Identifier : " << Name;
  out << ", ";
  out << "Value : ";
  Value->PrintOstream(out);

  out << " )";
}

void ComparisonExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Left Value : ";
  left_->PrintOstream(out);
  out << ", ";
  out << "Op Value : " << op_ << ", ";
  out << "Right Value : ";
  right_->PrintOstream(out);
  out << ", ";

  out << ")";
}

void BinaryExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Left Value : ";
  left_->PrintOstream(out);
  out << ", ";
  out << "Op Value : " << op_ << ", ";
  out << "Right Value : ";
  right_->PrintOstream(out);
  out << ", ";

  out << ")";
}

void IdentifierExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Name : " << identifier_;

  out << ")";
}

void NumberExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Value : " << tok_value_;

  out << ")";
}

void WhitespaceExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Value : '" << tok_value_;

  out << "' )";
}

void NullExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " ( Value : 'NULL' )";
}

void BooleanExpression::PrintOstream(std::ostream &out) const {
  out << NodeEnumToString(Type()) << " ( Value : '";
  out << boolean_ << "' )";
}
