#include "token.hpp"

#include <stdexcept>

Token::Token(){};
Token::Token(std::string trigger, TokenSymbol symbol)
    : _trigger(trigger), _symbol(symbol){};

std::string Token::trigger() { return _trigger; }
TokenSymbol Token::symbol() { return _symbol; }

TokenSet::TokenSet() { _count=0; }
TokenSet::TokenSet(std::vector<std::string> ss, std::vector<TokenSymbol> ts) {
  if (ss.size() != ts.size()) {
    throw new std::invalid_argument(
        "string vec and TokenSymbol vec must of matching length.");
  }

  _ss = ss;
  _ts = ts;
  _count = ss.size();
}

std::vector<std::string> TokenSet::triggers() { return _ss; }
std::vector<TokenSymbol> TokenSet::symbols() { return _ts; }

TokenSymbol TokenSet::match(std::string s) {
  for (unsigned int i = 0; i < _count; i++) {
    if (_ss[i] == s) {
      return _ts[i];
    }
  }

  return TokenSymbol::UNDEFINED;
}
