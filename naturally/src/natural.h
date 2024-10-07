#pragma once
// TODO: probably folder hierarchy mapping to ns makes sense.

#include <gmpxx.h>
#include <ostream>

namespace NumberSystems {

typedef unsigned long int ul;

typedef enum {
  ODD = 1,
  PRIME = 2,
  PERFECT = 4,
  TAXICAB = 8,

} NaturalProp;

class Natural {
public:
  Natural(mpz_class);
  Natural(mpz_class, ul);
  Natural(ul);
  void set_property(NaturalProp);
  void clear_property(NaturalProp);
  bool get_property(NaturalProp);

  friend std::ostream &operator<<(std::ostream &stream, const Natural &n) {
    return n.print(stream);
  }

  // TODO: is it better/worse to compare the strings?
  // how can we optimize/simplify/govern things more effectrively
  // given that we are only concerned with positive integers.
  // the string could be as large as we like...but how much longer does it take?
  // benchmark and see.
  // ...and/or simply refuse to acknowledge raw types...
  friend inline bool operator==(const Natural &lhs, const Natural &rhs) {
    return lhs._n.get_ui() == rhs._n.get_ui();
  }

  void operator=(const Natural &n) { _n = n._n; }

  friend inline bool operator<(const Natural &lhs, const Natural &rhs) {
    return lhs._n.get_ui() < rhs._n.get_ui();
  }

  // friend inline bool operator==(const Natural &lhs, const ul &rhs) {
  //   return lhs._n.get_ui() == rhs;
  // }

  // friend inline bool operator==(const ul &lhs, const Natural &rhs) {
  //   return lhs == rhs._n.get_ui();
  // }

protected:
  ul _properties = 0;
  mpz_class _n;

  std::ostream &print(std::ostream &stream) const;
};

typedef Natural N;
} // namespace NumberSystems
