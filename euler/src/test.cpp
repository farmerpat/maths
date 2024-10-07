#include <vector>

#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_preprocessor.hpp"
#include "catch2/internal/catch_string_manip.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "date_util.h"
#include "gmpxx.h"
#include "int_util.h"

using namespace Util;
using namespace Catch;
using namespace Catch::Matchers;

// TODO: (maybe). Sort out why << Catch2 can't see gmp's << overload
namespace Catch {
template <>
struct StringMaker<mpz_class> {
  static std::string convert(mpz_class const &value) { return value.get_str(); }
};
}  // namespace Catch

TEST_CASE("IntUtil", "[int-util]") {
  SECTION("IntUtil::proper_divisors") {
    std::vector<unsigned long> expected = {1, 3, 5};
    auto actual = IntUtil::proper_divisors(15);
    REQUIRE_THAT(actual, Equals(expected));
    expected = {1};
    actual = IntUtil::proper_divisors(2);
    REQUIRE_THAT(actual, Equals(expected));
    expected = {1, 2, 3};
    actual = IntUtil::proper_divisors(6);
  }

  SECTION("IntUtil::are_amicable") {
    REQUIRE(IntUtil::are_amicable(220, 284));
    REQUIRE(!IntUtil::are_amicable(23, 65));
  }

  SECTION("IntUtil::is_multiple_of") {
    REQUIRE(!IntUtil::is_multiple_of(2, 4));
    REQUIRE(IntUtil::is_multiple_of(9, 3));
    REQUIRE(IntUtil::is_multiple_of(9, 9));
    REQUIRE(!IntUtil::is_multiple_of(2, 3));
    REQUIRE(IntUtil::is_multiple_of(6, 2));
    REQUIRE(IntUtil::is_multiple_of(23, 1));
  }

  SECTION("IntUtil::is_even") {
    REQUIRE(IntUtil::is_even(0));
    REQUIRE(IntUtil::is_even(2));
    REQUIRE(IntUtil::is_even(-2));
    REQUIRE(IntUtil::is_even(4));
    REQUIRE(IntUtil::is_even(-4));
    REQUIRE(IntUtil::is_even(2004));
    REQUIRE(IntUtil::is_even(-2004));
    REQUIRE(!IntUtil::is_even(1));
    REQUIRE(!IntUtil::is_even(-1));
    REQUIRE(!IntUtil::is_even(23));
    REQUIRE(!IntUtil::is_even(-23));
  }

  SECTION("IntUtil::fibonacci") {
    REQUIRE(IntUtil::fibonacci(0) == 1);
    REQUIRE(IntUtil::fibonacci(1) == 2);
    REQUIRE(IntUtil::fibonacci(2) == 3);
    REQUIRE(IntUtil::fibonacci(3) == 5);
    REQUIRE(IntUtil::fibonacci(4) == 8);
    REQUIRE(IntUtil::fibonacci(5) == 13);
    REQUIRE(IntUtil::fibonacci(6) == 21);
    REQUIRE(IntUtil::fibonacci(7) == 34);
    REQUIRE(IntUtil::fibonacci(21) == 28657);
  }

  SECTION("IntUtil::is_prime") {
    REQUIRE(!IntUtil::is_prime(0));
    REQUIRE(!IntUtil::is_prime(1));
    REQUIRE(IntUtil::is_prime(2));
    REQUIRE(IntUtil::is_prime(3));
    REQUIRE(!IntUtil::is_prime(4));
    REQUIRE(IntUtil::is_prime(5));
    REQUIRE(IntUtil::is_prime(13));
    REQUIRE(IntUtil::is_prime(23));
    REQUIRE(!IntUtil::is_prime(32));
    REQUIRE(!IntUtil::is_prime(100));
    REQUIRE(!IntUtil::is_prime(132));
    REQUIRE(IntUtil::is_prime(9929));
  };

  SECTION("IntUtil::factors") {
    std::vector<long int> expected = {1, 2, 3, 6};
    std::vector<long int> actual;
    actual = IntUtil::factors(6);
    REQUIRE_THAT(actual, Equals(expected));
    expected = {1, 2, 3, 5, 6, 10, 15, 30};
    REQUIRE_THAT(IntUtil::factors(30), Equals(expected));
    expected = {1, 2};
    REQUIRE_THAT(IntUtil::factors(2), Equals(expected));
    expected = {1, 3};
    REQUIRE_THAT(IntUtil::factors(3), Equals(expected));
    expected = {1, 5};
    REQUIRE_THAT(IntUtil::factors(5), Equals(expected));
    expected = {1, 2, 4, 8};
    REQUIRE_THAT(IntUtil::factors(8), Equals(expected));
  }

  SECTION("IntUtil::filter") {
    std::vector<long int> expected = {1, 3, 5, 7, 9};
    std::vector<long int> actual = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    IntUtil::rm_if(actual, [](const long int &n) { return (n % 2 == 0); });
    REQUIRE_THAT(actual, Equals(expected));
  }

  SECTION("IntUtil::is_palindrome") {
    REQUIRE(IntUtil::is_palindrome(0));
    REQUIRE(IntUtil::is_palindrome(1));
    REQUIRE(IntUtil::is_palindrome(2));
    REQUIRE(IntUtil::is_palindrome(3));
    REQUIRE(IntUtil::is_palindrome(11));
    REQUIRE(IntUtil::is_palindrome(111));
    REQUIRE(!IntUtil::is_palindrome(23));
    REQUIRE(IntUtil::is_palindrome(1001));
    REQUIRE(!IntUtil::is_palindrome(2001));
  }

  SECTION("IntUtil::sum_of_squares") {
    REQUIRE(IntUtil::sum_of_squares(1) == 1);
    REQUIRE(IntUtil::sum_of_squares(2) == 5);
    REQUIRE(IntUtil::sum_of_squares(10) == 385);
  }

  SECTION("IntUtil::square_of_sums") {
    REQUIRE(IntUtil::square_of_sums(1) == 1);
    REQUIRE(IntUtil::square_of_sums(2) == 9);
    REQUIRE(IntUtil::square_of_sums(10) == 3025);
  }

  SECTION("IntUtil::nth_prime") {
    REQUIRE(IntUtil::nth_prime(1) == 2);
    REQUIRE(IntUtil::nth_prime(2) == 3);
    REQUIRE(IntUtil::nth_prime(3) == 5);
    REQUIRE(IntUtil::nth_prime(4) == 7);
    REQUIRE(IntUtil::nth_prime(5) == 11);
    REQUIRE(IntUtil::nth_prime(6) == 13);
  }

  SECTION("IntUtil::greatest_product_of_n_digits_in") {
    REQUIRE(IntUtil::greatest_product_of_n_digits_in(2, "987") == 72);
    REQUIRE(IntUtil::greatest_product_of_n_digits_in(2, "98799") == 81);
    REQUIRE(IntUtil::greatest_product_of_n_digits_in(1, "98799") == 9);
    REQUIRE(IntUtil::greatest_product_of_n_digits_in(3, "987990") == 567);
  }

  SECTION("IntUtil::is_pythagorean_triplet") {
    REQUIRE(IntUtil::is_pythagorean_triplet(3, 4, 5));
    REQUIRE(!IntUtil::is_pythagorean_triplet(3, 4, 7));
  }

  SECTION("IntUtil::triangle_number") {
    REQUIRE(IntUtil::triangle_number(1) == 1);
    REQUIRE(IntUtil::triangle_number(2) == 3);
    REQUIRE(IntUtil::triangle_number(3) == 6);
    REQUIRE(IntUtil::triangle_number(4) == 10);
    REQUIRE(IntUtil::triangle_number(5) == 15);
    REQUIRE(IntUtil::triangle_number(6) == 21);
    REQUIRE(IntUtil::triangle_number(7) == 28);
    REQUIRE(IntUtil::triangle_number(8) == 36);
    REQUIRE(IntUtil::triangle_number(9) == 45);
  }
  SECTION("IntUtil::collatz") {
    REQUIRE(IntUtil::collatz(1) == 4);
    REQUIRE(IntUtil::collatz(13) == 40);
  }

  SECTION("IntUtil::factorial") {
    mpz_class expected_result(120);
    REQUIRE(IntUtil::factorial(5) == expected_result);
    expected_result = 3628800;
    REQUIRE(IntUtil::factorial(10) == expected_result);
  }

  SECTION("IntUtil::sum_of_digits") {
    REQUIRE(IntUtil::sum_of_digits("32") == 5);
    REQUIRE(IntUtil::sum_of_digits("90321") == 15);
    REQUIRE(IntUtil::sum_of_digits("3628800") == 27);
    REQUIRE(IntUtil::sum_of_digits("000003628800") == 27);
  }
}

TEST_CASE("DateUtil", "[date-util]") {
  SECTION("DateUtil::is_leap_year") {
    REQUIRE(!DateUtil::is_leap_year(1802));
    REQUIRE(DateUtil::is_leap_year(1804));
    REQUIRE(DateUtil::is_leap_year(1904));
    // not on a century unless divisible by 400
    REQUIRE(DateUtil::is_leap_year(2000));
    REQUIRE(DateUtil::is_leap_year(2384));
    REQUIRE(DateUtil::is_leap_year(2400));
    REQUIRE(!DateUtil::is_leap_year(2401));
  }

  SECTION("DateUtil::days_per_month") {
    REQUIRE(DateUtil::days_per_month(2323, 1) == 31);
    REQUIRE(DateUtil::days_per_month(2323, 2) == 28);
    REQUIRE(DateUtil::days_per_month(2000, 2) == 29);
    REQUIRE(DateUtil::days_per_month(1930, 3) == 31);
    REQUIRE(DateUtil::days_per_month(1930, 10) == 31);
    REQUIRE(DateUtil::days_per_month(1930, 4) == 30);
  }

  SECTION("DateUtil::roll_day_of_week") {
    Date_ d{.year = 1901, .month = 1, .date = 1, .day_of_week = 1};
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 2);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 3);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 4);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 5);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 6);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 7);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 1);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 2);
    d.roll_day_of_week();
    REQUIRE(d.day_of_week == 3);
  }

  SECTION("DateUtil::tomorrow") {
    Date_ d{.year = 1901, .month = 1, .date = 1, .day_of_week = 1};
    DateUtil::tomorrow(d);

    REQUIRE(d.year == 1901);
    REQUIRE(d.month == 1);
    REQUIRE(d.date == 2);
    REQUIRE(d.day_of_week == 2);
    d.month = 2;
    d.date = 27;
    DateUtil::tomorrow(d);
    DateUtil::tomorrow(d);
    REQUIRE(d.year == 1901);
    REQUIRE(d.month == 3);
    REQUIRE(d.date == 1);

    // a leap year
    d.year = 1904;
    d.month = 2;
    d.date = 28;
    DateUtil::tomorrow(d);
    REQUIRE(d.month == 2);
    REQUIRE(d.date == 29);
    DateUtil::tomorrow(d);
    REQUIRE(d.month == 3);
    REQUIRE(d.date == 1);
  }
}
