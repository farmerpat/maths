#include "natural.h"
#include <gmpxx.h>

namespace NumberSystems {
Natural::Natural(ul n) {
  mpz_class temp;
  temp = n;
  _n = temp;
}

Natural::Natural(mpz_class n) {
  // TODO: throw an error?
  if (n < 1)
    _n = 1;
  else
    _n = n;
}

Natural::Natural(mpz_class n, unsigned long int properties) : Natural(n) {
  _properties = properties;
}

std::ostream &Natural::print(std::ostream &stream) const {
  stream << _n.get_str(10);
  return stream;
}

} // namespace NumberSystems
