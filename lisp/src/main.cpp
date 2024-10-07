// clang-format off
#include <stdio.h>

// clang-format on
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

#include <iostream>
//#include <reader.hpp>
#include <string>
#include <token.hpp>

#include "scanner.hpp"

int main(int argc, char **argv) {
  bool done = false;
  Scanner scanner;

  // TODO: if we aren't using done, rm it.
  while (!done) {
    char *line = readline("> ");

    if (!line) {
      std::cout << "Exiting on EOF." << std::endl;
      break;
    }

    // if it's not the emtpy string.
    if (*line) {
      // then we want to pass it to the parser.
      // TODO: I don't yet know if we want a string or char*.
      if (strcmp(line, "exit") == 0) {
        free(line);
        break;
      }

      add_history(line);
      std::string l(line);
      std::cout << "sending, " << l << " to the scanner..." << std::endl;
      std::vector<Token> tokens = scanner.scan(l);

      std::cout << "received the following tokens:\n";
      for (int i=0; i<tokens.size(); i++) {
        Token t = tokens[i];
        std::cout << t.trigger() << ", " <<
          token_symbol_to_string(t.symbol()) << std::endl;
      }
    }

    free(line);
  }

  std::cout << "listen carefully now, my son..." << std::endl;
  std::cout << "All Done." << std::endl;

  return 0;
}
