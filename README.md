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

## Project Structure
```
AParser
├── CMakeLists.txt
├── file                      // Read the file that contains the code
│   ├── CMakeLists.txt
│   ├── file.cpp
│   └── file.hpp
├── lexer                   // Read the text of the code and convert to token.
│   ├── CMakeLists.txt
│   ├── lexer.cpp
│   └── lexer.hpp
├── LICENSE
├── main.cpp
├── operator
│   ├── CMakeLists.txt
│   ├── operator.cpp
│   └── operator.hpp
├── parser                  // Convert to AST Syntax
│   ├── CMakeLists.txt
│   ├── parser.cpp
│   └── parser.hpp
├── README.md
├── rmcmake.sh
├── stringutil              // Utility for string manipulation
│   ├── CMakeLists.txt
│   ├── stringutil.cpp
│   └── stringutil.hpp
├── testing
│   ├── CMakeLists.txt
│   ├── test_stringutil.cpp
└── token                   // Generate Token and define Token type
    ├── CMakeLists.txt
    ├── token.cpp
    └── token.hpp
```