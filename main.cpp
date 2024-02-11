#include <iostream>
#include <queue>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"

// Set limit of printing token from one lexer
#define DEBUG_SET_PRINT_LIMIT false
#define PREVENT_LOOP_MAX_COUNT 10

int main() {
  std::string input;
  std::queue<TokenPtr> tokqueue;

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
      tokqueue.push(tok);

#if DEBUG_SET_PRINT_LIMIT
      if (countLoop > PREVENT_LOOP_MAX_COUNT) break;
      countLoop++;
#endif
    } while ((*tok).Type() != TokenType::EOL);

    tokqueue.push(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr)));

    Parser parser = Parser(tokqueue);
    Program program = parser.ProduceAST();

    std::cout << program << std::endl;
    tokqueue = std::queue<TokenPtr>();
  } while (input != "exit");
}
