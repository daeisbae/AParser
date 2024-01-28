#ifndef OPERATOR_H
#define OPERATOR_H

#include <memory>
#include <string>

class Operator {
public:
    enum OperatorType {
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
    enum OpDirection {
        LEFT,
        BOTH,
        RIGHT
    };

private:
    OperatorType optype;
    OpDirection opdir;
    std::string input;
    bool overloadable;
    int precedence;

public:
    Operator(std::string input, OperatorType opType, OpDirection opDirection, bool isOverloadable, int precedence);
    ~Operator();

    OpDirection OperatorDirection() const;
    OperatorType OperatorType() const;
    std::string TextInput() const;
    bool IsOverloadable() const;
    int Precedence() const;
};

typedef std::shared_ptr<Operator> OperatorPtr;

#endif