#include <string>
#include <cctype>

#include "lexer.hpp"
#include "file.hpp"


Lexer::Lexer(FilePtr fileptr) {
    this->file = fileptr;
    line = 1;
    text = fileptr->ReadLine(line);
    currPos = 0;
    nextPos = 1;
    readCh();
}

Lexer::Lexer(std::string input) {
    currPos = 0;
    nextPos = 1;
    text = input;
    readCh();
}

Lexer::~Lexer() {}

void Lexer::moveNextPos() {
    currPos++;
    nextPos++;
}

char Lexer::peek() {
    return text.at(nextPos);
}

void Lexer::readCh() {
    currCh = text.at(currPos);
}

std::string Lexer::readStr() {
    if(text.at(currPos) != '"') throw WrongLexingException();

    moveNextPos();
    readCh();

    std::string str_val = "";
    
    while(currCh != '"') {
        str_val.push_back(currCh);
        moveNextPos();
        readCh();
    }

    moveNextPos();
    readCh();

    return str_val;
}

std::string Lexer::readNum() {
    if(std::isdigit(text.at(currPos))) throw WrongLexingException();

    moveNextPos();
    readCh();

    std::string num_val = "";
    
    while(!std::isdigit(currCh)) {
        num_val.push_back(currCh);
        moveNextPos();
        readCh();
    }

    moveNextPos();
    readCh();

    return num_val;
}

TokenPtr Lexer::NextToken() {
    for(;;) {
        bool isdigit = std::isdigit(currCh);
        bool isalpha = std::isalpha(currCh);

        // Check whether it is for literal or number

        switch(currCh) {
            case '\n':
                // Generate EOL Operator
                break;
            case '+':
            case '-':
            case '/':
            case '*':
                // Generate Operator
                break;
            default:
                // Maybe used for literal validation
                break;
        }
    }
}