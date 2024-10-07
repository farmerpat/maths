#include <iostream>
#include <string>
#include <vector>

#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_preprocessor.hpp"
#include "catch2/internal/catch_string_manip.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "token.hpp"

using namespace Catch;
using namespace Catch::Matchers;

CATCH_REGISTER_ENUM(TokenSymbol, TokenSymbol::QUOTE, TokenSymbol::LPAREN,
                    TokenSymbol::RPAREN);

TEST_CASE("LISP", "[Token and Friends]") {
  SECTION("Testing Token") {
    Token t("'", TokenSymbol::QUOTE);
    REQUIRE(t.trigger() == "'");
    REQUIRE(t.symbol() == TokenSymbol::QUOTE);
  }

  SECTION("Testing TokenSet...maybe") {
    std::vector<std::string> trigs = {"'", "(", ")"};
    std::vector<TokenSymbol> symbs = {TokenSymbol::QUOTE, TokenSymbol::LPAREN,
                                      TokenSymbol::RPAREN};
    TokenSet ts(trigs, symbs);
    // ez. I just have a bug.
    TokenSymbol s = ts.match("'");
    REQUIRE(s == TokenSymbol::QUOTE);
    REQUIRE(ts.symbols() == symbs);
  }
}
