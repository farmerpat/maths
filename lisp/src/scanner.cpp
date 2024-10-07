#include <string.h>
#include "scanner.hpp"

Scanner::Scanner() {
  _knonw_tokens = TokenSetFactory::LispZeroTokenSet();
}

std::vector<Token> Scanner::scan(std::string line) {
  std::vector<Token> tokens;
  char buffer[100];
  unsigned int buffer_pos = 0;
  const char *raw = line.c_str();
  bool in_sym = false;
  bool in_num = false;
  unsigned int len = strlen(raw);
  char c;

  for (unsigned int i=0; i<len; i++) {
    c = raw[i];

    if (isblank(c)) {
      continue;
    }

    switch (c) {
      case '(':
        tokens.push_back(Token({c}, TokenSymbol::LPAREN));
        break;
      case ')':
        tokens.push_back(Token({c}, TokenSymbol::RPAREN));
        break;
      case '\'':
        tokens.push_back(Token({c}, TokenSymbol::QUOTE));
        break;
      default:
        if (isdigit(c)) {
          buffer_pos = 0;
          buffer[0] = 0;

          char current;
          for (buffer_pos=0;;buffer_pos++) {
            current = *(raw+i+buffer_pos);
            if (isdigit(current)) {
              buffer[buffer_pos] = current;

            } else {
              // then we're done.
              buffer[buffer_pos] = 0;
              // -1 to "retract" the first char outside sym.
              i += buffer_pos-1;
              std::string s(buffer);
              tokens.push_back(Token(s, TokenSymbol::ATOM));
              break;

            }
          }
        } else if (isalpha(c)) {
          buffer_pos = 0;
          buffer[0] = 0;

          char current;
          for (buffer_pos=0;;buffer_pos++) {
            current = *(raw+i+buffer_pos);
            if (isalpha(current)) {
              buffer[buffer_pos] = current;
            } else {
              // then we're done.
              buffer[buffer_pos] = 0;
              // -1 to "retract" the first char outside sym.
              i += buffer_pos-1;
              std::string n(buffer);
              tokens.push_back(Token(n, TokenSymbol::ATOM));
              break;
            }
          }
        } else {
          tokens.push_back(Token({c}, TokenSymbol::UNDEFINED));
          // TODO: probably scream about it...
        }
        break; // end default:
    } // end switch
  } // end for

  // TODO: 
  // assume single character triggers for now.
  
  return tokens;
}

/* old scan body
for (unsigned int i=0; i<line.length(); i++) {
    char c = line[i];
    const char *raw = line.c_str();
    int digits_parsed = 0;
    int successful_parses = 0;

    if (isblank(c)) {
      continue;
    }

    // TODO:
    // you know what this means.
    // deal w/ it.
    // if (c == EOL) {
    // }
    // i think "( foo" input resulting in infinite loop
    // is either b/c no EOL or 
    // i+=digits_parsed-1;
    // is incorrect. use the debugger tui ftw.
    // you can make this happen with patience
    // and persistence.
    if (c == '(') {
      tokens.push_back(Token({c}, TokenSymbol::LPAREN));
    } else if (c == ')') {
      tokens.push_back(Token({c}, TokenSymbol::RPAREN));
    } else if (c == '\'') {
      tokens.push_back(Token({c}, TokenSymbol::QUOTE));
    } else if (isdigit(c)) {
      // TODO: worry about floats
      successful_parses = 0;
      digits_parsed = 0;
      unsigned long numin = 0;
      buffer[0] = 0;

      int successful_parses = sscanf(
          raw+i,
          "%[0-9]%n",
          buffer,
          &digits_parsed
      ); 

      digits_parsed = strlen(buffer);
      numin = std::atoi(buffer);
      i+=digits_parsed-1;
      std::string trigger(buffer);
      tokens.push_back(Token(trigger, TokenSymbol::ATOM));

    } else if (isalpha(c)) {
      // TODO "smithers!" is recognized as a token.
      // huh? off by one error or alpha does not mean
      // what I think it means.
      successful_parses = 0;
      digits_parsed = 0;
      buffer[0] = 0;

      int successful_parses = sscanf(
          raw+i,
          "%[A-Z]%n",
          buffer,
          &digits_parsed
      ); 

      i+=digits_parsed-1;
      std::string trigger(buffer);
      tokens.push_back(Token(trigger, TokenSymbol::ATOM));
    } else {
      tokens.push_back(Token({c}, TokenSymbol::UNDEFINED));
    }
  }


 */
