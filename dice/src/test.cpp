#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_preprocessor.hpp"
#include "catch2/internal/catch_string_manip.hpp"
#include "catch2/matchers/catch_matchers.hpp"

using namespace Catch;
using namespace Catch::Matchers;

TEST_CASE("Algebras", "[main]") {
  SECTION("Testing things") {
    // test things.
    REQUIRE(1 == 1);
  }
}
