#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

#include "token.hpp"
#include "file.hpp"

class Lexer {
private:
    FilePtr file;
    std::string text;
    int currPos;
    int nextPos;
    int line;
    char currCh;


    void moveNextPos();
    char peek();
    void readCh();
    // Parse the string
    std::string readStr();
    // Parse the number
    std::string readNum();
    // Parse the literal (variable/function naming)
    std::string readLiteral();

public:
    Lexer(std::string input);
    Lexer(FilePtr fileptr);
    ~Lexer();

    TokenPtr NextToken();
};

class WrongLexingException : public std::exception {
public:
    std::string what() {
        return "Unexpected value in the line.";
    }
};

#endif