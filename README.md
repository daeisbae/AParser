# Parser
This is a programming language project that is **not working**. But will be aiming to be fully working.
It's a project built tp understand the concept of how lexers and parsers work in detail.

## How to build and execute the program
```sh
cmake .
cmake --build .
chmod +x Parser
./Parser
```

## Project Structure
```
Parser
├── CMakeLists.txt
├── file.cpp
├── file.hpp                // Read the file that contains the code
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
└── token                   // Generate Token and define Token type
    ├── operator.cpp
    ├── operator.hpp
    ├── token.cpp
    └── token.hpp
```