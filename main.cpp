#include <iostream>
#include <string>

#include "lexer.hpp"

// Set limit of printing token from one lexer
#define DEBUG_SET_PRINT_LIMIT false
#define PREVENT_LOOP_MAX_COUNT 10

int main() {
  std::string input;

  do {
    std::cout << ">>> ";
    std::getline(std::cin, input);

    Lexer lexer = Lexer(input);
    TokenPtr tok;

    #if DEBUG_SET_PRINT_LIMIT
      int countLoop = 0;
    #endif

    do {
      tok = lexer.NextToken();
      std::cout << *tok << std::endl;
      
      #if DEBUG_SET_PRINT_LIMIT
        if(countLoop > PREVENT_LOOP_MAX_COUNT) break;
        countLoop++;
      #endif
    } while ((*tok).Type() != TokenType::EOL);

  } while (input != "exit");
}
