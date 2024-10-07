#include <ctype.h>
#include <functional>
#include <iostream>

#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_preprocessor.hpp"
#include "catch2/internal/catch_string_manip.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "gmpxx.h"
#include "hanoi.hpp"
#include "natural.h"

using namespace Catch;
using namespace Catch::Matchers;
using namespace NumberSystems;

// TODO: (maybe). Sort out why << Catch2 can't see gmp's << overload
namespace Catch {
template <> struct StringMaker<mpz_class> {
  static std::string convert(mpz_class const &value) { return value.get_str(); }
};
} // namespace Catch

TEST_CASE("Recurence/Iterate Equivalence", "Hanoi") {
  SECTION("hanoi_r is equivalent to hanoi_i") {
    // basis
    mpz_class n(0);
    mpz_class expected_result(0);
    REQUIRE(hanoi_r(n) == expected_result);
    REQUIRE(hanoi_i(n) == expected_result);

    n = 1;
    expected_result = 1;
    REQUIRE(hanoi_r(n) == expected_result);
    REQUIRE(hanoi_i(n) == expected_result);

    n = 2;
    expected_result = 3;
    REQUIRE(hanoi_r(n) == expected_result);
    REQUIRE(hanoi_i(n) == expected_result);

    n = 3;
    expected_result = 7;
    REQUIRE(hanoi_r(n) == expected_result);
    REQUIRE(hanoi_i(n) == expected_result);

    n = 4;
    expected_result = 15;
    REQUIRE(hanoi_r(n) == expected_result);
    REQUIRE(hanoi_i(n) == expected_result);

    n = 10;
    expected_result = 1023;
    REQUIRE(hanoi_r(n) == expected_result);
    REQUIRE(hanoi_i(n) == expected_result);
    n = 23;
    expected_result = 8388607;
    REQUIRE(hanoi_r(n) == expected_result);
    REQUIRE(hanoi_i(n) == expected_result);
  }
}

TEST_CASE("NumberSystems", "Natural") {
  SECTION("Natural Can Instantiate and compare with integers") {
    N n1(1);
    N n2(23);
    ul n = 1;
    REQUIRE(n1 == n1);
    REQUIRE(n1 == n);
    n = 3;
    n1 = 3;
    // HOW?
    REQUIRE(n1 == n);
    REQUIRE(n1 == n);
    REQUIRE(n1 == n);
    REQUIRE(n1 == n);
    REQUIRE(n1 == n);
    // HERE: possible sane way of comparing types.
    // sanity checks...confused about why can say n1 == n w/o overload...
    // perhaps they've overloaded it.
    REQUIRE(typeid(n1) == typeid(Natural));
    REQUIRE(typeid(n) == typeid(ul));

    n = 23;
    n1 = 19;

    // ...okay...
    // I think that somehow it's casting this to a Natural.
    // maybe because there's a constructor that takes this type
    // normal behavior is to attempt cast by calling "appropriate"
    // constructor...unexpected and kind and kind of confusing...
    REQUIRE(n1 < n);
    n1 = 2001;
    // REQUIRE(n1 > n);
  }
}
