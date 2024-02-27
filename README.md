# AParser
This is a programming language project that is **not working**. But will be aiming to be fully working.
It's a project built to understand the concept of how lexers and parsers work in detail.

## How to build and execute the program
### Prerequisit
- CMake
- GCC/G++

### Installation
```sh
git clone https://github.com/daeisbae/AParser.git
cd AParser
cmake .
cmake --build .
chmod +x AParser
./AParser
```

## Learning Grammar Syntax of AParser
Refer [AParser Language Syntax Documentation](https://github.com/daeisbae/AParser/blob/main/docs/README.md)

## Project Structure
```
AParser
├── CMakeLists.txt
├── LICENSE
├── README.md
├── main.cpp
├── rmcmake.sh
├── ast                     // Defines the Abstract Syntax Tree (Expressions and Statements)
│   ├── CMakeLists.txt
│   ├── ast.cpp
│   └── ast.hpp
├── docs
│   └── README.md
├── file                    // Read the file that contains the code
│   ├── CMakeLists.txt
│   ├── file.cpp
│   └── file.hpp
├── lexer                   // Read the text of the code and convert to token.
│   ├── CMakeLists.txt
│   ├── lexer.cpp
│   └── lexer.hpp
├── operator
│   ├── CMakeLists.txt
│   ├── operator.cpp
│   └── operator.hpp
├── parser                  // Converts to AST Syntax
│   ├── CMakeLists.txt
│   ├── parser.cpp
│   └── parser.hpp
├── runtime
│   ├── CMakeLists.txt
│   ├── runtime.cpp
│   └── runtime.hpp
├── stringutil              // Utility for string manipulation
│   ├── CMakeLists.txt
│   ├── stringutil.cpp
│   └── stringutil.hpp
├── testing
│   ├── CMakeLists.txt
│   ├── test_lexer.cpp
│   ├── test_main.cpp
│   ├── test_runtime.cpp
│   └── test_stringutil.cpp
└── token                   // Generate Token and define Token type
    ├── CMakeLists.txt
    ├── token.cpp
    └── token.hpp
```