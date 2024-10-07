#include <cmath>
#include <iostream>
#include <numbers>
#include <random>
#include <vector>

typedef unsigned long long ull;
typedef unsigned int ui;

inline bool divides(ull n, ull m) { return m % n == 0; }

inline ull floor_sqrt(ull n) {
  ull max = 0;
  // TODO: more intelligently, please.
  for (ull i = 1; i < n; i++) {
    if (i * i <= n) {
      std::cout << "new max for " << n << ": " << i << std::endl;
      max = i;
    }
  }
  return max;
}
inline bool is_even(ull n) { return n % 2 == 0; }

std::vector<ull> divisors(ull n) {
  std::vector<ull> divisors;
  for (ull i = 1; i <= n; i++) {
    if (divides(i, n)) {
      divisors.push_back(i);
    }
  }

  return divisors;
}

// TODO: what's on the faces, etc.
class D {
 public:
  D(ui faces) : _faces(faces) {
    // TODO: this seems expensive.
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, faces);
    _dist = dist;
  }

  ui roll() { return _dist(_rng); }

 protected:
  ui _faces;
  std::mt19937 _rng;
  std::uniform_int_distribution<std::mt19937::result_type> _dist;
};

class CachedPrimes {
 public:
  CachedPrimes();
  bool is_prime(ull n) {
    if (n < 2) return 0;

    return false;
  }

 protected:
  std::vector<ull> _known_primes;
};

bool is_prime(ull n) {
  if (n < 2) return false;

  auto divs = divisors(n);
  if (divs.size() == 2) return true;
  return false;
}

// std::numbers::pi is just a hard-coded constant.
// if we generated our own approximation based on high
// number of terms for decimal expanions re: gmp.
std::pair<ull, ull> approximate_pi(ull max_ator) {
  std::pair<ull, ull> approximation;
  ull best_numerator = 1;
  ull best_denominator = 1;
  auto pi = std::numbers::pi;
  double closest_dist = 100;

  for (ull numerator = 1; numerator < max_ator; ++numerator) {
    for (ull denominator = 1; denominator < max_ator; ++denominator) {
      double this_appx = (double)numerator / (double)denominator;
      double this_dist = std::abs(pi - this_appx);
      if (this_dist < closest_dist) {
        closest_dist = this_dist;
        best_numerator = numerator;
        best_denominator = denominator;
      }
    }
  }

  approximation.first = best_numerator;
  approximation.second = best_denominator;

  return approximation;
}

std::vector<ull> possible_primes(ull num_faces, ull num_dice) {
  ull min = num_dice;
  ull max = num_faces * num_dice;
  // ull prime_count = 0;

  std::vector<ull> primes;
  for (ull i = min; i <= max; i++) {
    if (is_prime(i)) {
      primes.push_back(i);
    }
  }

  // how close can we get to pi with a rational number?
  // not the expansion...some simple n/m, perhaps very large.

  return primes;
}

int main(void) {
  std::cout << "hello, Carl!" << std::endl;
  // const int num_faces = 6;
  // D d6(num_faces);

  ull max_num_faces = 50;
  ull max_num_dice = 1;

  for (ull num_faces = 2; num_faces <= max_num_faces; num_faces++) {
    for (ull num_dice = 1; num_dice <= max_num_dice; num_dice++) {
      auto primes = possible_primes(num_faces, num_dice);
      ull num_primes = primes.size();
      ull possible_combinations = std::pow(num_faces, num_dice);

      std::cout << num_dice << " D" << num_faces << ": ";
      std::cout << num_primes << " | " << possible_combinations << " = "
                << (double)num_primes / possible_combinations << std::endl;
    }

    // std::cout << std::endl;
  }

  return 0;
}

// auto pieces_of_pie = approximate_pi(std::numeric_limits<ull>::max());
// auto pieces_of_pie = approximate_pi(232323UL);
// auto pieces_of_pie = approximate_pi(232300UL);

// std::cout << "pieces of pie: " << pieces_of_pie.first << std::endl;
// std::cout << "                -----------------" << std::endl;
// std::cout << "               " << pieces_of_pie.second << std::endl;
