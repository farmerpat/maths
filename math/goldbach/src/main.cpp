#include <gmpxx.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// NOTE:
// Goldbach's conjecture:
// Every even natural number > 2
// is the sum of two prime numbers.

class NaturalGenerator {
 public:
  NaturalGenerator() : _n(1) {}
  NaturalGenerator(mpz_class n) : _n(n) {}
  mpz_class next() {
    // what happens if I simply return _++ instead?
    // a/b profile it somehow!
    mpz_class next_value(_n++);
    return next_value;
  }

 protected:
  mpz_class _n;
};

struct Pair {
  mpz_class left;
  mpz_class right;

  std::string to_string() {
    return "(" + left.get_str(10) + ", " + right.get_str(10) + ")";
  }
};

inline bool is_even(mpz_class n) { return n % 2 == 0; }
inline bool is_odd(mpz_class n) { return n % 2 == 1; }

// TODO: probably PrimeCachce class.
std::vector<mpz_class> PRIMES;

inline bool divides(mpz_class n, mpz_class m) { return m % n == 0; }

std::vector<mpz_class> get_divisors(mpz_class n) {
  // this seems wrong...where did i get the idea from?
  // auto break_point = std::sqrt(n.get_d());
  auto break_point = n;
  std::vector<mpz_class> divisors = {1};

  for (mpz_class candidate(2); candidate <= break_point; candidate++) {
    if (divides(candidate, n)) {
      divisors.push_back(candidate);
    }
  }

  return divisors;
}

bool is_prime(mpz_class n) {
  // NOTE: assume we cached 2...
  if (n == 2) return true;
  if (is_even(n)) {
    return false;
  }

  auto divisors = get_divisors(n);
  if (divisors.size() == 2) {
    return true;
  }
  return false;
}

mpz_class cached_prime(mpz_class n) {
  // if there is an nth - 1 elt...
  auto len = PRIMES.size();
  if ((n - 1) < len) {
    return PRIMES[n.get_ui() - 1];
  }
  return mpz_class(0);
}

mpz_class nth_prime(mpz_class n) {
  auto cached = cached_prime(n);
  if (cached) {
    return cached;
  }

  std::cout << "no cache hit for " << n.get_str()
            << "...generating primes...\n";
  auto highest_current_prime_index = PRIMES.size() - 1;
  auto highest_current_prime = PRIMES[PRIMES.size() - 1];

  // TODO: use the divisible by 6 neighbor thing...this is too slow.
  for (mpz_class candidate(highest_current_prime + 2);
       highest_current_prime_index <= n.get_ui(); candidate += 2) {
    if (is_prime(candidate)) {
      PRIMES.push_back(candidate);
      highest_current_prime_index++;
      // std::cout << "found " << highest_current_prime_index << "th prime: " <<
      // std::cout << PRIMES[highest_current_prime_index].get_str() <<
      // std::endl;
      if (highest_current_prime_index % 100 == 0) {
        std::cout << "found prime number " << highest_current_prime_index
                  << "..." << PRIMES[highest_current_prime_index].get_str()
                  << std::endl;
      }
    }

    // if (highest_current_prime_index == n) {
    //   return PRIMES[highest_current_prime_index];
    // }
  }

  std::cout << "highest_current_prime_index: " << highest_current_prime_index
            << std::endl;
  std::cout << "its prime: " << PRIMES[highest_current_prime_index].get_str()
            << std::endl;

  return mpz_class(-1);
}

Pair find_goldbach(mpz_class n) {
  if (!is_even(n)) {
    return Pair{-1, -1};
  }

  // we need to start with our smallest prime
  // inner loop starting also with smallest prime
  // break when we find a winner...
  // TODO: what if we "run out" of primes?
  auto known_primes = PRIMES.size();

  for (mpz_class i(0); i < known_primes; i++) {
    auto prime_a = PRIMES[i.get_ui()];

    for (mpz_class j(0); j < known_primes; j++) {
      auto prime_b = PRIMES[j.get_ui()];

      if ((prime_a + prime_b) == n) {
        return Pair{prime_a, prime_b};
      }
    }
  }

  return Pair{-1, -1};
}

void load_primes() {
  std::ifstream prime_file;
  prime_file.open("./primes.txt", std::ios::in);

  std::string line;

  while (std::getline(prime_file, line)) {
    mpz_class this_prime(line);
    PRIMES.push_back(this_prime);
  }
}

void dump_primes() {
  std::ofstream prime_file;
  // just clobber it.
  prime_file.open("./primes.txt", std::ios::out);

  for (mpz_class i(0); i < PRIMES.size(); i++) {
    prime_file << PRIMES[i.get_ui()].get_ui() << std::endl;
  }

  prime_file.close();
}

int main(void) {
  NaturalGenerator ng;
  mpz_class n;

  load_primes();

  // for (mpz_class i(1); i <= 32; i++) {
  //   auto p = nth_prime(i);
  //   std::cout << i.get_str() << "th prime: " << p.get_str() << std::endl;
  // }

  // for (mpz_class i(4); i < 12; i += 2) {
  //   auto gb = find_goldbach(i);
  //   std::cout << "g(" << i.get_str(10) << ") -> " << gb.to_string()
  //             << std::endl;
  // }

  // timing nth_prime vs sieve of Eratosthenes, getting 664579 primes...
  auto p = nth_prime(664579);
  std::cout << "nth prime: " << p.get_str() << std::endl;

  dump_primes();

  return 0;
}
