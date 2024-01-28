# Parser
This is a programming language project that is **not working**. But will be aiming to be fully working.
It's a project built to understand the concept of how lexers and parsers work in detail.

## How to build and execute the program
### Prerequisit
- CMake
- GCC/G++

### Installation
```sh
git clone https://github.com/daeisbae/Parser.git
cd Parser
cmake .
cmake --build .
chmod +x Parser
./Parser
```

## Project Structure
```
Parser
├── CMakeLists.txt
├── io                      // Read the file that contains the code
│   ├── file.cpp
│   └── file.hpp
├── lexer                   // Read the text of the code and convert to token.
│   ├── lexer.cpp
│   └── lexer.hpp
├── LICENSE
├── main.cpp
├── parser                  // Convert to AST Syntax
│   ├── parser.cpp
│   └── parser.hpp
├── README.md
├── rmcmake.sh
├── stringutil              // Utility for string manipulation
│   ├── stringutil.cpp
│   └── stringutil.hpp
└── token                   // Generate Token and define Token type
    ├── operator.cpp
    ├── operator.hpp
    ├── token.cpp
    └── token.hpp
```