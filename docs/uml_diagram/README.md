# Project Structure in UML Diagram
## Lexer Structure
```mermaid
---
title: AParser - Lexing (Tokenization)
---
classDiagram

    Lexer ..> Token : "Converts the Text to List of Tokens"
    Lexer ..> Operator : "Converts the Operator to List of Tokens"
    File "1" --> "1" Lexer : "Reads the File"
    Token o-- "0..1" Operator : "Contains the Operator"
    Token --> TokenType : "Has"
    Operator --> OperatorType : "Has"

    class Lexer{
        +NextToken() TokenPtr
        +GetReservedKeywordTokenType() TokenType
    }

    class TokenType{
        <<enumeration>>
        EOL
        INVALID
        IDENTIFIER
        WHITESPACE
        SET
        INTEGER
        STRING
        BOOL
        IF
        FOR
        FUNCTION
        RETURN
        OPERATOR
    }

    class Token{
        +Type() TokenType
        +Text() String
        +OpPtr() OperatorPtr
    }

    class OperatorType{
        <<enumeration>>
        DOT
        COLON
        COMMA
        PLUS
        MINUS
        STAR
        SLASH
        L_BRACE
        R_BRACE
        L_PARENTHESIS
        R_PARENTHESIS
        L_BRACKET
        R_BRACKET
        EQUAL
        NOT_EQUAL
    }

    class File{
        ReadLine(const int line) String
    }
    
    class Operator{
        +Direction() OpDirection
        +Type() OperatorType
        +TextInput() String
        +IsOverloadable() bool
        +Precedence() int
    }
```

### Operator Precedence for Arithmetic Operation
| Operator Type               | Precedence |
|-----------------------------|------------|
| EQUAL, NOT_EQUAL            | 1          |
| ASSIGN                      | 2          |
| L_BRACE, R_BRACE            | 3          |
| L_PARENTHESIS, R_PARENTHESIS| 4          |
| PLUS, MINUS                 | 5          |
| STAR, SLASH                 | 6          |
| Others                      | 7          |


## AST and Parser
```mermaid
---
title: AParser - AST and Parsing
---
classDiagram
    Parser "1" --> "1" Program : "Produces"
    Parser "1" --> "1..n" Statement : "Parses"
    Parser "1" --> "1..n" Expression : "Parses"
    Program "1" --> "1..n" Statement : "Contains"
    Statement <|-- Expression
    Statement <|-- VariableDeclarationStatement
    Expression <|-- BinaryExpression
    Expression <|-- IdentifierExpression
    Expression <|-- IntegerExpression
    Expression <|-- WhitespaceExpression
    Expression <|-- NullExpression
    Expression <|-- BooleanExpression
    Expression <|-- VariableAssignExpression
    Expression <|-- ComparisonExpression

    class Parser{
        -tok_queue_: std::queue<TokenPtr>
        +ProduceAST(tokenQueue: std::queue<TokenPtr>&): Program
        -ParseStatement(): StatementPtr
        -ParseExpression(): ExpressionPtr
        -ParsePrimaryExpression(): ExpressionPtr
        -ParseAdditionExpression(): ExpressionPtr
        -ParseMultiplicationExpression(): ExpressionPtr
        -ParseWhitespaceExpression(): ExpressionPtr
        -ParseIdentifierDeclarationExpression(): StatementPtr
        -ParseIdentifierAssignmentExpression(): ExpressionPtr
        -ParseComparisonExpression(): ExpressionPtr
    }

    class Program{
        +body_: std::queue<StatementPtr>
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class Statement{
        <<abstract>>
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class Expression{
        <<abstract>>
    }

    class VariableDeclarationStatement{
        +identifier_: string
        +value_: ExpressionPtr
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class BinaryExpression{
        +left_: ExpressionPtr
        +right_: ExpressionPtr
        +op_: string
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class IdentifierExpression{
        +identifier_: string
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class IntegerExpression{
        +tok_value_: int
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class WhitespaceExpression{
        +tok_value_: string
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class NullExpression{
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class BooleanExpression{
        +boolean_: string
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class VariableAssignExpression{
        +Name: string
        +Value: StatementPtr
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }

    class ComparisonExpression{
        +left_: ExpressionPtr
        +op_: string
        +right_: ExpressionPtr
        +Type(): NodeType
        +PrintOstream(out: std::ostream&): void
    }
```