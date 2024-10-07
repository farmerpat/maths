#include <gmpxx.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

inline bool divides(mpz_class n, mpz_class m) { return m % n == 0; }

// want primes from set of first n numbers...
struct MpzPC {
  mpz_class n;
  bool prime;
};

const unsigned long SIEVE_SIZE = 10000001;
MpzPC CANDIDATES[SIEVE_SIZE] = {};

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

  unsigned long prime_count = 0;
  for (unsigned long i = 0; i < SIEVE_SIZE; i++) {
    if (CANDIDATES[i].prime) {
      prime_count++;
      std::cout << CANDIDATES[i].n.get_str() << std::endl;
    }
  }

  std::cout << "number of primes: " << prime_count << std::endl;

  // TODO: how can we pit this, temporaly, against naive approach?
  // I want to see how much better this is if at all...

  // number of primes: 664579
  // ./sieve  0.85s user 0.96s system 99% cpu 1.814 total

  // QUESTION: is there some way to supercede the finite limitation of this
  // sieve?

  return 0;
}
