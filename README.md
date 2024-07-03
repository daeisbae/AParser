# AParser
This is a experimental programming language project. It's a project built to understand the concept of how lexers and parsers work in detail.

**Current Status:** Include documentation and refactor code

## How to build and execute the program
### Prerequisite
- CMake (If using Manual installtion)
- GCC/G++ (If using Manual installtion)
- Docker (If using docker based installation)

### Manual Installation
```sh
git clone https://github.com/daeisbae/AParser.git
cd ~/AParser
cmake .
cmake --build .
chmod +x AParser
./AParser
```

### Docker Based Installation
```sh
cd ~/Aparser
docker build -t aparser .
docker run --rm -it --name aparser aparser
```

## Learning Grammar Syntax of AParser
Refer [AParser Language Syntax Documentation](https://github.com/daeisbae/AParser/blob/main/docs/README.md)

## Coding Style
This project aims to follow [Google C++ Code Convention](https://google.github.io/styleguide/cppguide.html)

## UML Diagram
Refer [AParser UML Diagram - Class Association](https://github.com/daeisbae/AParser/blob/main/docs/uml_diagram/README.md)

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
