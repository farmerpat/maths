#include <gmpxx.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct MpzPC {
  mpz_class n;
  bool prime;
};

inline bool divides(mpz_class n, mpz_class m) { return m % n == 0; }

const unsigned long SIEVE_SIZE = 10000001;
std::vector<mpz_class> PRIMES = {-1};
MpzPC CANDIDATES[SIEVE_SIZE] = {};

std::vector<mpz_class> divisors(mpz_class n) {
  std::vector<mpz_class> divs;
  for (mpz_class i(1); i <= n; i++) {
    if (divides(i, n)) {
      divs.push_back(i);
    }
  }
  return divs;
}

// I think that we might be able to repeatedly divide by the smallest
// prime number that divides the current result.
// e.g. n=20
// current=n
// current==20
// 2|current
// current/=2
// current==10
// 2|current
// current/=2
// current==5
// not two, not 3 but five divides.
// 5|current
// current /=5
// current == 1 and we're done.
std::vector<mpz_class> prime_factors(mpz_class n) {
  std::vector<mpz_class> pfs;
  mpz_class current(n);
  mpz_class current_prime_index(1);

  while (current != 1) {
    auto this_pf = PRIMES[current_prime_index.get_ui()];
    if (divides(this_pf, current)) {
      pfs.push_back(this_pf);
      current /= this_pf;
    } else {
      current_prime_index++;
    }
  }

  return pfs;
}

int main(void) {
  // seed sieve.
  for (unsigned long i = 0; i < SIEVE_SIZE; i++) {
    CANDIDATES[i] = MpzPC{.n = i, .prime = true};
  }

  // 0th and 1st are bunk.
  CANDIDATES[0].prime = false;
  CANDIDATES[1].prime = false;

  for (unsigned long i = 2; i < SIEVE_SIZE; i++) {
    if (!CANDIDATES[i].prime) {
      // then isn't it broken?
      continue;
    }

    // assume current is prime.
    // the step size to clobber is i.
    for (unsigned long j = 1; (i + (i * j)) < SIEVE_SIZE; j++) {
      CANDIDATES[i + (i * j)].prime = false;
    }
  }

  for (unsigned long j = 1; j < SIEVE_SIZE; j++) {
    auto c = CANDIDATES[j];
    if (c.prime) {
      PRIMES.push_back(c.n);
    }
  }

  for (unsigned long j = 1; j < PRIMES.size() / 4096; j++) {
    std::cout << PRIMES[j].get_str() << std::endl;
  }

  // want a function that builds N from iterating over prime factors.
  // perhaps listing the first few members of n by their prime factors
  // will reveal a pattern.

  // work backwards...how do we compute the prime factors of an integer n?

  // what about the sum of a composite's pfs?
  for (mpz_class i(1); i < 11; i++) {
    // auto divs = divisors(i);
    auto pfs = prime_factors(i);
    std::cout << i.get_str() << ": [";
    for (int i = 0; i < pfs.size(); i++) {
      std::cout << pfs[i].get_str() << ((i == pfs.size() - 1) ? "" : ", ");
    }
    std::cout << "]" << std::endl;
  }

  return 0;
}
