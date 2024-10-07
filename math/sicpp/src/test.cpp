#include <vector>

#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_preprocessor.hpp"
#include "catch2/internal/catch_string_manip.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "gmpxx.h"

using namespace Catch;
using namespace Catch::Matchers;

// TODO: (maybe). Sort out why << Catch2 can't see gmp's << overload
namespace Catch {
template <>
struct StringMaker<mpz_class> {
  static std::string convert(mpz_class const &value) { return value.get_str(); }
};
}  // namespace Catch

TEST_CASE("Parent", "Child") {
  SECTION("Grandchild") { REQUIRE(1 == 1); }
}
