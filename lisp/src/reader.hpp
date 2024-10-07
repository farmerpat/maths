#pragma once
#include <string>
#include <vector>

#include "token.hpp"

// Token(std::string trigger, TokenSymbol symbol)

class Reader {
 public:
  Reader();
  // Reader(std::unordered_map<std::string, Token>);
  std::vector<Token> scan(std::string);

 protected:
  TokenSet _knonw_tokens;
};
