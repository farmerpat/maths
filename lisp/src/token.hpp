#pragma once
#include <string>
#include <vector>

enum class TokenSymbol { UNDEFINED, LPAREN, RPAREN, QUOTE, ATOM, DEFINE };

static std::string token_symbol_to_string(TokenSymbol sym) {
  if (sym == TokenSymbol::UNDEFINED) {
    return "UNDEFINED";
  } else if (sym == TokenSymbol::LPAREN) {
    return "LPAREN";
  } else if (sym == TokenSymbol::RPAREN) {
    return "RPAREN";
  } else if (sym == TokenSymbol::QUOTE) {
    return "QUOTE";
  } else if (sym == TokenSymbol::ATOM) {
    return "ATOM";
  } else if (sym == TokenSymbol::DEFINE) {
    return "DEFINE";
  }

  return "";
}


// TODO: Token needs an atomic value.
class Token {
 public:
  Token();
  Token(std::string trigger, TokenSymbol symbol);
  std::string trigger();
  TokenSymbol symbol();

 protected:
  std::string _trigger;
  TokenSymbol _symbol;
};

class TokenSet {
 public:
  TokenSet();
  TokenSet(std::vector<std::string>, std::vector<TokenSymbol>);
  TokenSymbol match(std::string);
  std::vector<std::string> triggers();
  std::vector<TokenSymbol> symbols();

 protected:
  std::vector<std::string> _ss;
  std::vector<TokenSymbol> _ts;
  unsigned long _count;
};

class TokenSetFactory {
 public:
  static TokenSet LispZeroTokenSet() {
    return TokenSet(
        {"(", ")", "'"},
        {TokenSymbol::LPAREN, TokenSymbol::RPAREN, TokenSymbol::QUOTE}
    );
  }
};
