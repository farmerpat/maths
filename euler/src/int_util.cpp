#include "int_util.h"

#include <algorithm>
#include <iostream>
#include <sstream>

namespace Util {

bool IntUtil::are_amicable(unsigned long m, unsigned long n) {
  auto m_divisors = proper_divisors(m);
  auto n_divisors = proper_divisors(n);
  std::function<unsigned long(unsigned long, unsigned long)> l =
      [](unsigned long a, unsigned long b) -> unsigned long { return a + b; };

  unsigned long m_divisor_sum = reduce(m_divisors, l, (unsigned long)0);
  unsigned long n_divisor_sum = reduce(n_divisors, l, (unsigned long)0);

  if (m_divisor_sum == n && n_divisor_sum == m) {
    return true;
  }

  return false;
}

std::vector<unsigned long> IntUtil::proper_divisors(unsigned long n) {
  std::vector<unsigned long> divisors;
  for (unsigned long i = 1; i < n; i++) {
    if (divides(i, n)) {
      divisors.push_back(i);
    }
  }
  return divisors;
}

int IntUtil::fibonacci(int n) {
  if (n == 0) return 1;
  if (n == 1) return 2;
  int this_n_minus_1 = 2;
  int this_n_minus_2 = 1;
  int tmp;

  for (int i = 2; i <= n; i++) {
    tmp = this_n_minus_2 + this_n_minus_1;
    this_n_minus_2 = this_n_minus_1;
    this_n_minus_1 = tmp;
  }

  return this_n_minus_1;
}

bool IntUtil::is_prime(long int n) {
  if (n < 2) return false;
  if (n == 2 || n == 3) return true;
  if (n % 2 == 0) return false;

  for (long int divisor = 3; divisor < n; divisor += 2) {
    if (divides(divisor, n)) return false;
  }
  return true;
}

std::vector<long int> IntUtil::factors(long int n) {
  std::vector<long int> factors = {};
  if (n < 1) return factors;

  for (long int i = 1; i <= n; ++i) {
    if (divides(i, n)) {
      factors.push_back(i);
    }
  }

  return factors;
}

void IntUtil::rm_if(std::vector<long int> &v, std::function<bool(long int)> f) {
  v.erase(std::remove_if(v.begin(), v.end(), f), v.end());
}

bool IntUtil::is_palindrome(int n) {
  std::stringstream st;
  st << n;
  std::string s;
  st >> s;

  std::string reversed(s);
  std::reverse(s.begin(), s.end());

  if (s == reversed) {
    return true;
  }

  return false;
}

long IntUtil::sum_of_squares(long n) {
  if (n < 1) return 0;

  long result = 0;
  for (int i = 1; i <= n; i++) {
    result += i * i;
  }

  return result;
}

long IntUtil::square_of_sums(long n) {
  if (n < 1) return 0;
  long sum = 0;
  for (int i = 0; i <= n; i++) {
    sum += i;
  }
  return sum * sum;
}

long IntUtil::nth_prime(long n) {
  if (n < 1) return 0;
  if (n == 1) return 2;
  // if (n == 2) return 3;
  long prime_count = 1;
  long candidate = 3;

  while (prime_count < n) {
    if (is_prime(candidate)) {
      if (++prime_count >= n) break;
    }
    candidate += 2;
  }
  return candidate;
}

long IntUtil::greatest_product_of_n_digits_in(long n, std::string digits) {
  long result = 0;
  long len = digits.length();
  int left_pos = 0;
  int window_size = n;

  for (int left_pos = 0; left_pos <= len - window_size; left_pos++) {
    std::string this_chunk = digits.substr(left_pos, window_size);
    long product = 1;
    for (int i = 0; i < window_size; i++) {
      product *= this_chunk[i] - '0';
    }

    if (product > result) {
      result = product;
    }
  }

  return result;
}

bool IntUtil::is_pythagorean_triplet(long a, long b, long c) {
  if (!(a < b && b < c)) return false;
  return (a * a + b * b) == c * c;
}

std::vector<Triplet> IntUtil::get_all_triplets_before(int target) {
  std::vector<Triplet> result;
  for (int i = 1; i < target; ++i) {
    for (int j = i + 1; j < target; j++) {
      for (int k = j + 1; k < target; k++) {
        result.push_back(Triplet{.a = i, .b = j, .c = k});
      }
    }
  }

  return result;
}

std::vector<Triplet> IntUtil::get_all_pythagorean_triplets_before(int target) {
  std::vector<Triplet> result;
  for (int i = 1; i < target; ++i) {
    for (int j = i + 1; j < target; j++) {
      for (int k = j + 1; k < target; k++) {
        if (is_pythagorean_triplet(i, j, k)) {
          result.push_back(Triplet{.a = i, .b = j, .c = k});
        }
      }
    }
  }

  return result;
}

std::vector<long> IntUtil::primes_below(int n) {
  std::vector<long> result;
  if (n < 2) return result;

  long max = n - 1;
  if (is_even(max)) {
    --max;
  }

  for (long i = max; i > 1; i -= 2) {
    if (is_prime(i)) {
      result.push_back(i);
    }
  }

  result.push_back(2);

  return result;
}

long IntUtil::triangle_number(long n) {
  long result = 0;

  for (int i = 1; i <= n; i++) {
    result += i;
  }

  return result;
}

long IntUtil::collatz(long n) {
  if (n < 1) return -1;
  if (is_even(n)) {
    return n / 2;
  }
  return 3 * n + 1;
}

std::vector<long> IntUtil::collatz_seq(long n) {
  std::vector<long> result = {n};
  long this_collatz = n;

  while (this_collatz != 1) {
    this_collatz = collatz(this_collatz);
    result.push_back(this_collatz);
  }

  return result;
}

mpz_class IntUtil::factorial(unsigned long n) {
  mpz_class prod(1);
  for (int i = 1; i <= n; i++) {
    prod *= i;
  }

  return prod;
}

unsigned long IntUtil::sum_of_digits(std::string digits) {
  // NOTE: could reduce via divisions of 10...better?
  unsigned long sum = 0;

  for (unsigned int c = 0; c < digits.length(); c++) {
    sum += digits[c] - '0';
  }

  return sum;
}
}  // namespace Util
