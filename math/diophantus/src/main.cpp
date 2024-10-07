#include <gmpxx.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// class Natural {
//  public:
//   Natural();
// };
//
// typedef Natural N;
//
// TODO: what if there was some way to ask the system questions about numbers?
// why isn't there a dictionary to record results?

// TODO: what I really want is a reusable way to create caching functions.
// perhaps could specify n threshold for caching...e.g. maybe we don't care
// about caching factorials for n smaller than 5.
// at the simplest, we can us a vector.
// since we're currently only concerned with natural numbers, we can cache n
// by using it as the index of our cache vector.
// but what if we want to extend this to Z?
// what if we want a representation of Q at some point?
// TODO:
// e.g. was looking up Euler's number. Can be computed as sum of infinite series
// of rationals.
// e.g. there ought to be a way to mixin caching.
// an abstract class might do.
// maybe it makes sense to create a class to serve as the representation of a
// function.
// TODO:
// e.g. testing for primality.
// e.g. nth prime.
// e.g. nth term of any given (in)fiinite series...
// think.
// consider also generalization for multithreading.
// are there any fundamental operations that are thread safe?
// can common operations be decomposed into thread safe subops?

// TODO: consider generalization of sieve.
// our sieve of Eratothsanes flags future members based on divisibility...
// a step size is calculated and the remainder of the sieve is stepped over,
// flagging members at unit size.
// Then this is different from a collection of the integers we care about.
// TODO:
// This is the entire collection of naturals up to N with some property
// affliated with each particular value of n.
// e.g. instead of {1,3,5,7,9...} we have
// {[1,true],[2,false],[3,true],[4,false],[5,true]...}
// perhaps all the extra space is not wasted.
// imagine n different properties.
// imagine a representation of members of N s.t. we might query for properties
// of n.
// TODO:
// perhaps a vector of property items...
// cooler is an unsiged int which has a value of the logical and of all
// properties possessed by this number. this way we can arbitrarily add
// properties on numbers...e.g. an enum. and just append to the end.
// think...probably carefully about boolean maths.
enum NaturalProp { EVEN = 2, ODD, PRIME };

// NOTE: what about cycling a range of natural representations
// through memory? e.g. once n becomes very large, i have no clue
// how large mpz_class becomes.

// NOTE: want to generate the sequence of the smallest integer
// representable by n squares.
// "" n cubes.
// etc.

// NOTE:
// what about "conspiracy composites" which are composite numbers
// which have 23 as a prime divisor?
// such a number is called a conspirator.

// NOTE: the distance between terms of a particular sequence
// vs the distance along the natural numberline between occurrences
// of property, p0.
// consider the ratio of these distances.
// do any numeric properties also
// appear as sort of a reflection
// somehow feels related to a mapping...
// e.g. sequences whose members are growth relation of other sequences.
// its like sequences being used to describe one another.
// again, what about other properties of N?
// what about chaining sequences functions together?
// might there be some relation between individual sequences
// and their generator function's composition?

// which positive integers can be expressed as the sum of two squares?
// is there some threshold above which all n will be representable as the sum of
// two squares?
// program the machine for answer.

// in how many ways may a given natural be expressed as a sum of two squares?
// of three cubes?
// of three squares?
// of two cubes? (re: taxicab numbers.)

// could you potentially improve the upper bound on the 7th taxicab number?
// and get credit for it?
// is there some such contribution you could make
// that could be cited on a CV?
// perhaps you can demonstrate research potential.
// perhaps GRE scores don't matter if research potential + they like you.
// people like you when you are yourself.
// especially intelligent and sensitive people.
// think.
//

// TODO: want a way to test some_trip == null_triple
// like..
// what I REALLY want
// is a way to have
// if (some_triple)
// be false if some_triple is s.t.
// x=-1; y=-1; z=-1
// or whatever.
// (since triples are assumed to positive integers, -1 made sense
// as sentinel)
//
//
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
  // TODO: duplicates: 3,4,5 == 4,3,5?
  // probably cast them out.
  // how many pythagorean triples exist for
  // x,y,z <= 100?
  // std::vector<triple> pythagorean_triples = get_pythagorean_triples(23);
  // print_triples(pythagorean_triples);

  // TODO:use something like https://github.com/AlexanderAgd/CLIST
  // and rewrite this in C.
  // if it's faster and we aren't using classes, who cares?
  // you basically think in structs anyways...

  // in how many ways can n be expressed as a sum of two squares?
  // NOTE: If I'm only concerned with natural numbers, then 0 == uninitialized.
  mpz_class smallest_sos_in_n_ways[100];
  smallest_sos_in_n_ways[0] = mpz_class(-1);
  std::vector<pair> smallest_sos_exprs[100];
  smallest_sos_exprs[0] = std::vector<pair>{pair{-1, -1}};

  mpz_class j(0);
  mpz_class n(0);
  mpz_class have_ps(0);
  mpz_class lb(1);
  mpz_class ub(100001);
  mpz_class current_num_sos_exprs(1);
  bool quiet = true;

  for (n = lb; n <= ub; n++) {
    auto ps = as_pair_of_squares(n);
    if (!ps.empty()) {
      have_ps++;
      if (!quiet) {
        std::cout << n.get_str() << ": ";
      }

      if (ps.size() == current_num_sos_exprs) {
        smallest_sos_in_n_ways[current_num_sos_exprs.get_ui()] = n;
        smallest_sos_exprs[current_num_sos_exprs.get_ui()] = ps;

        std::cout
            << "the smallest natural representable as the sum of two "
               "squares in "
            << current_num_sos_exprs.get_ui() << " different ways is "
            << smallest_sos_in_n_ways[current_num_sos_exprs.get_ui()].get_str()
            << std::endl;

        current_num_sos_exprs++;
      }

      for (j = 0; j < ps.size(); ++j) {
        auto p = ps[j.get_ui()];
        if (!quiet) {
          std::cout << "(" << p.x.get_str() << ", " << p.y.get_str() << ") ";
        }

        // TODO: configure auto formatter thing to put single newline
        // at close of inmost scope bracket. e.g. the line above this comment.
      }
    } else {
      if (!quiet) {
        std::cout << n.get_str() << ":0";
      }
    }

    if (!quiet) {
      std::cout << std::endl;
    }
  }

  if (!quiet) {
    std::cout
        << std::endl
        << "there were " << have_ps.get_str() << " integers from "
        << lb.get_str() << " -> " << ub.get_str()
        << " that can be represented as the sum of two squares in at least "
           "one way."
        << std::endl;
  }

  for (mpz_class i(1); i <= current_num_sos_exprs; i++) {
    std::cout
        << "the smallest natural representable as the sum of two squares in "
        << i.get_str() << " different ways is "
        << smallest_sos_in_n_ways[i.get_ui()].get_str() << std::endl;
  }

  return 0;
}
