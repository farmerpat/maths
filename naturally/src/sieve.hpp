// #pragma once why not?
// want primes from set of first n numbers...
#include <gmpxx.h>
#include <iostream>
#include <ostream>
#include <vector>

inline bool divides(mpz_class a, mpz_class b) { return b % a == 0; }

// NOTE: starting braindead static.
// NOTE: size might matter re: dynamic sieve...
// maybe we always want a square.
// maybe it makes things a lot faster.
// consider remember powers of 2.
// consider halving things etc...

// what is the best representation for a sieve mask?
// the prime itself (e.g. step size)?
// needn't we be concerned with offset?
// maybe we assume they all start at 0th position which is
// the n=1th prime.
// maybe the move is to always start at the beginning of the current
// sieve chunk
// and keep applying all known primes as masks
// until the prime we are applying > sqrt(SIEVE_CHUNK_SIZE)
// or whatever.

// NOTE: could use a sentinel of -1 instead of MpzPC.
struct MpzPC {
  mpz_class n;
  bool prime;
};

// TODO: what if this piece was merely a helper
// for some other process responsible for keeping track of which primes
// we know about and which we don't.
// what I mean to say is, what if we were just asking about a chunk of a larger
// sieve, and this process was responsible for generating it..
// if we ensure the right shape/placement of candidates, then
// the client of this would need to know which N we are starting with,
// and which primes are already known.

// const unsigned long SIEVE_SIZE = 10000001;
// TODO: PAY ATTN! size probably matters...think powers of 2...
// think...
// maybe must needs be power of 10?
// maybe could be leveraged if size constraint.
const unsigned long SIEVE_SIZE = 10;
MpzPC CANDIDATES[SIEVE_SIZE] = {};

// NOTE: sieve dimensions might be variable.
// different dimensions might prove optimal
// for various ranges of n.

std::vector<mpz_class> gen_primes(std::vector<mpz_class> known_primes,
                                  mpz_class start) {
  std::vector<mpz_class> new_primes;
  mpz_class largest_candidate = start + SIEVE_SIZE;

  for (mpz_class i{0}; i < SIEVE_SIZE; i++) {
    CANDIDATES[i.get_ui()] = MpzPC{.n = start + i, .prime = true};
  }

  if (start == 0) {
    CANDIDATES[0].prime = false;
    CANDIDATES[1].prime = false;
  }

  // we've got to mask the thing given all known primes less than whatever.
  // for most use cases, it's probably all the known primes.
  // e.g. if we're starting a previously unmapped segment of our sieve
  // then our starting number is surely larger than our largest known prime.
  // that said, we can calculate the largest value to be considered for
  // primality within this sieve segment. then can't we stop testing primes if
  // they have some relationship to largest n other than prime > n? of
  // course....if the prime is greater than the sqrt(largest_n) then aren't we
  // done? try it and see. wouldn't it be nice to proceed confidently?

  for (mpz_class i{0}; i < known_primes.size(); i++) {
    mpz_class this_prime = known_primes[i.get_ui()];

    // TODO: first and 2nd...for first time through...think of edge case, baboo.
    for (mpz_class i{0}; i < SIEVE_SIZE; i++) {
      auto this_candidate = CANDIDATES[i.get_ui()];
      if (divides(this_prime, this_candidate.n)) {
        // then we need to mark as composite all members of CANDIDATES from here
        // through the end by a size of i*k +prime
        // no. it's j from j=i -> end j+= prime.
        for (mpz_class j{i}; j < SIEVE_SIZE; j += this_prime) {
          CANDIDATES[j.get_ui()].prime = false;
        }
        break;
      }
    }
  }

  for (unsigned long i = 0; i < SIEVE_SIZE; i++) {
    if (!CANDIDATES[i].prime) {
      // skip 0,1
      continue;
    }
  }

  return new_primes;
}

std::vector<mpz_class> generate_sieve_primes() {
  std::vector<mpz_class> primes;

  for (unsigned long i = 0; i < SIEVE_SIZE; i++) {
    CANDIDATES[i] = MpzPC{.n = i, .prime = true};
  }

  // 0 and 1 are bunk.
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

  for (unsigned long i = 0; i < SIEVE_SIZE; i++) {
    if (CANDIDATES[i].prime) {
      primes.push_back(CANDIDATES[i].n);
    }
  }

  return primes;
}
