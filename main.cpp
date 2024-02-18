#include <iostream>
#include <queue>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"
#include "runtime.hpp"
#include "token.hpp"

// Set limit of printing token from one lexer
#define DEBUG_SET_PRINT_LIMIT false
#define PREVENT_LOOP_MAX_COUNT 10

int main() {
  std::string input;
  std::queue<TokenPtr> tokqueue;
  Parser parser = Parser();

  Evaluater evaluater = Evaluater();

  do {
    std::cout << ">>> ";
    std::getline(std::cin, input);
    if (input == "exit") return 0;

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
    } while (tok->Type() != TokenType::EOL);

    // If null input, continue
    if (tokqueue.front()->Type() == TokenType::EOL) {
      tokqueue.pop();
      continue;
    }

    tokqueue.push(GenerateToken("", TokenType::EOL, OperatorPtr(nullptr)));

    // Parse the token and produce Abstract Syntax Tree (AST)
    Program program = parser.ProduceAST(tokqueue);

    // Evaluate the AST and produce the result in string
    std::cout << evaluater.EvaluateProgram(program) << std::endl;

    // Reset the token queue
    tokqueue = std::queue<TokenPtr>();
  } while (true);
}
