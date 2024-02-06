#include <iostream>
#include <string>

#include "lexer.hpp"

int main() {
  std::string input;

  do {
    std::cout << ">>> ";
    std::getline(std::cin, input);

    Lexer lexer = Lexer(input);
    TokenPtr tok;

    do {
      tok = lexer.NextToken();
      std::cout << *tok << std::endl;
    } while ((*tok).Type() != TokenType::EOL);

  } while (input != "exit");
}
