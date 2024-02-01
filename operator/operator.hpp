#ifndef OPERATOR_H
#define OPERATOR_H

#include <memory>
#include <string>

enum class OperatorType {
    // General
    DOT,
    COLON,
    COMMA,

    // Calculation
    PLUS,
    MINUS,
    STAR,
    SLASH,

    // Brackets, Braces, Parenthesis
    L_BRACE,
    R_BRACE,
    L_PARENTHESIS,
    R_PARENTHESIS,
    L_BRACKET,
    R_BRACKET,

    // Comparison
    EQUAL,
    NOT_EQUAL,
};

// Used for the Brackets, Braces, Parenthesis direction.
enum class OpDirection { LEFT, BOTH, RIGHT };

class Operator {
private:
    OperatorType optype;
    OpDirection opdir;
    std::string input;
    bool overloadable;
    int precedence;

public:
    Operator(std::string input, OperatorType opType, OpDirection opDirection, bool isOverloadable, int precedence);
    ~Operator();

    OpDirection Direction() const;
    OperatorType Type() const;
    std::string TextInput() const;
    bool IsOverloadable() const;
    int Precedence() const;
};

typedef std::shared_ptr<Operator> OperatorPtr;

OperatorPtr GenerateOp(const std::string& input, OperatorType opType, OpDirection opDirection);

#endif