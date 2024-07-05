# Project Structure in UML Diagram
## Lexer Structure
```mermaid
---
title: AParser - Lexing (Tokenization)
---
classDiagram
    File "1" --> "1" Lexer : "Reads the File"
    Token "1..n" --* "1" Lexer : "Converts the Text to List of Tokens"
    Operator "1" --> "1" Token  : "If is Operator Token"
    TokenType "1" --> "1" Token : "Checks the Type"
    OperatorType "1" --> "1" Operator : "Checks the Operator Type"
    OpDirection "1" --> "1" Operator : "Operator Direction"

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

    class OpDirection {
        <<enumeration>>
        LEFT
        BOTH
        RIGHT
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