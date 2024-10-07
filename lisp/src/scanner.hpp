#pragma once
#include "token.hpp"

#include <iostream>
#include <string>
#include <vector>

class Scanner {
 public:
  Scanner();
  std::vector<Token> scan(std::string);

 protected:
  // e.g. {{'(', LPAREN}...}
 // std::unordered_map<char, Token> _punctuation;
  // maping from sets of characters that trigger scans,
  // e.g. {'a','b','c', etc...indeed there may be predefined
  // sets available. I'll roll my own.
  //std::unordered_map<std::set<char>, std::string> _scanners;
  TokenSet _knonw_tokens;

};
