#include "ast.hpp"

std::string NodeEnumToString(NodeType nodetype) {
  std::string typestr;

  switch (nodetype) {
    case NodeType::Program:
      typestr = "ProgramStatement";
      break;
    case NodeType::IdentifierExpr:
      typestr = "IdentifierExpression";
      break;
    case NodeType::IntegerExpr:
      typestr = "IntegerExpression";
      break;
    case NodeType::BinaryExpr:
      typestr = "BinaryExpression";
      break;
    default:
      typestr = "InvalidExpression";
      break;
  }
  return typestr;
}

void Program::PrintOstream(std::ostream& out) const {
  out << NodeEnumToString(Type()) << " {\n";

  for (const StatementPtr statement : Body) {
    statement->PrintOstream(out);
    out << "\n";
  }

  out << "}";
}

void BinaryExpression::PrintOstream(std::ostream& out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Left Value : ";
  Left->PrintOstream(out);
  out << ", ";
  out << "Op Value : " << OP << ", ";
  out << "Right Value : ";
  Right->PrintOstream(out);
  out << ", ";

  out << ")";
}

void IdentifierExpression::PrintOstream(std::ostream& out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Name : " << Name;

  out << ")";
}

void IntegerExpression::PrintOstream(std::ostream& out) const {
  out << NodeEnumToString(Type()) << " (";

  out << "Value : " << Value;

  out << ")";
}