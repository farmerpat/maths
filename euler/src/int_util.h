#pragma once

#include <functional>
#include <string>
#include <vector>

#include "f_util.h"
#include "gmpxx.h"

namespace Util {

struct Triplet {
  int a;
  int b;
  int c;
};

// TODO make this a template. you're nuts.
inline bool divides(unsigned long int n, unsigned long int m) {
  return m % n == 0;
}
inline bool divides(long int n, long int m) { return m % n == 0; }
inline bool divides(int n, int m) { return m % n == 0; }

// TODO: e.g. IntUtil::naturals(10) -> [1 2 3 ... 10]
// ...perhaps ::integers, ::reals...
class IntUtil {
 public:
  static std::vector<unsigned long> proper_divisors(unsigned long n);
  static bool are_amicable(unsigned long, unsigned long);
  static bool is_multiple_of(int n, int m) { return n % m == 0; };
  static bool is_even(int n) { return n == 0 || (n % 2) == 0; }
  // returns the nth fibonacci number where n is non-negative.
  static int fibonacci(int n);
  static bool is_prime(long int n);
  // returns vector of the factors of natural number n.
  static std::vector<long int> factors(long int n);
  static bool is_palindrome(int n);
  // destructively filters v with integer predicate f
  static void rm_if(std::vector<long int> &v, std::function<bool(long int)> f);

  // TODO NatUtil? These don't all operate across Z
  // for a natural number n, return the sum of the squares
  // of the first n natural numbers.
  static long sum_of_squares(long n);

  // for a natural number n, return the square
  // of the sum of the first n natural numbers.
  static long square_of_sums(long n);

  static long nth_prime(long n);

  static long greatest_product_of_n_digits_in(long n, std::string digits);
  static bool is_pythagorean_triplet(long a, long b, long c);
  static std::vector<Triplet> get_all_triplets_before(int target);
  static std::vector<Triplet> get_all_pythagorean_triplets_before(int target);
  static std::vector<long> primes_below(int n);
  // the nth triangle number, being the sum of the first n naturals.
  static long triangle_number(long n);
  static long collatz(long n);
  static std::vector<long> collatz_seq(long n);
  static mpz_class factorial(unsigned long);
  static unsigned long sum_of_digits(std::string);
};
}  // namespace Util
