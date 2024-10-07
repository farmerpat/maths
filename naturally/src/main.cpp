#include <gmpxx.h>

#include <iostream>
#include <string>
#include <vector>

#include "creppl.hpp"
#include "hanoi.hpp"
#include "sieve.hpp"

// TODO: there's got to be a better way...
// could overload...there is a name for this.
// think back to c# days.
// it's simply unpacking arguments...
// it's really like apply
// yet it's also concerned with presentation of result...
std::string evaluator(std::vector<CrepplParam> params) {
  mpz_class a = params[0].value();

  mpz_class result = a * a;

  return result.get_str();
}

// TODO:probably make this hold Ns and retry.
typedef struct {
  mpz_class x;
  mpz_class y;
} pair;

typedef struct {
  mpz_class x;
  mpz_class y;
  mpz_class z;
} triple;

inline mpz_class square(mpz_class n) { return n * n; }

std::vector<pair> as_pair_of_squares(mpz_class n) {
  // iterate until one of the squares is >= n
  std::vector<pair> pairs;

  for (mpz_class i(1); square(i) < n; i++) {
    for (mpz_class j(1); j <= i / 1 && square(j) < n; j++) {
      if (square(i) + square(j) == n) {
        pair p{i, j};
        pairs.push_back(p);
      }
    }
  }

  return pairs;
}

bool is_pythagorean_triple(triple trip) {
  return (square(trip.x) + square(trip.y)) == square(trip.z);
}

std::vector<triple> get_pythagorean_triples(mpz_class n) {
  std::vector<triple> triples;
  for (mpz_class x(1); x <= n; x++) {
    // if (x % 10 == 0) { std::cout << "x=" << x.get_str() << std::endl; }
    for (mpz_class y(1); y <= n; y++) {
      for (mpz_class z(1); z <= n; z++) {
        triple this_triple{x, y, z};
        if (is_pythagorean_triple(this_triple)) {
          triples.push_back(this_triple);
        }
      }
    }
  }

  return triples;
}

void print_triples(std::vector<triple> trips) {
  mpz_class trip_count(0);
  for (mpz_class i(0); i < trips.size(); i++) {
    triple trip = trips[i.get_ui()];
    trip_count++;
    std::cout << trip.x.get_str() << ", " << trip.y.get_str() << ", "
              << trip.z.get_str() << std::endl;
  }
}

void print_pairs(std::vector<pair> pairs) {
  mpz_class pair_count(0);
  for (mpz_class i(0); i < pairs.size(); i++) {
    pair pair = pairs[i.get_ui()];
    pair_count++;
    std::cout << pair.x.get_str() << ", " << pair.y.get_str() << ", "
              << std::endl;
  }
}

int main(void) {
  std::function<std::string(std::vector<CrepplParam>)> fn = evaluator;
  std::vector<CrepplParam> params{
      CrepplParam("n:", CrepplParamType::INT),
  };

  std::vector<CrepplFnSpec> fns{CrepplFnSpec{fn, "square", "sq"}};

  // Creppl repl(fn, params);
  // Creppl repl(fns);
  // repl.run();

  // mpz_class n(0);
  // std::cout << n.get_str() << std::endl;
  std::vector<mpz_class> primes = generate_sieve_primes();

  mpz_class hr;

  for (unsigned long i{1}; i < 23; i++) {
    // hr = hanoi_r(i);
    std::cout << i << ": " << two_to_the_n_minus_one(i).get_str() << std::endl;
    std::cout << i << ": " << two_to_the_n_minus_one_plus_one(i).get_str()
              << std::endl;
  }

  return 0;
}
