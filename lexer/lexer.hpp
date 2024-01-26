#include "../token/token.hpp"
#include "std::string"

class Lexer {
private:
    std::string& input;
    unsigned int currPos;
    unsigned int nextPos;
    char currCh;

    // Used to peek the next character to get the full literal, number or others.
    char peek();
    // Get the current location of the Ch and pass it to currCh
    void readCh();
    // Parse the string -> Used for the literal
    std::string readStr();
    // Parse the number -> Used for the integer value
    std::string readNum();
    // Remove the space between tokens
    void removeSpace();
public:
    Lexer(std::string& input);

    Token::Token NextToken();
}