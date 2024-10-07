#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

// TODO: just e.g. pointers surely more efficient
// when the time comes.
// ...otoh do you really want that refactor?
// the compiler was having none of this.
// union ATOM {
//   std::int64_t n;
//   std::string s;
// };

// then a universe is a set of atoms....
// a set is a collection of atoms.

// a field is a set on which +,-,*,/ are defined
// and behave "like a 4th grader expects".(?)

// a class is a set whose members all satisfy some property.

// a structure is a set provided with some features:
// features: operation, relation, metric, topology.

// an algebraic structure consists of a non-empty set
// (underlying set, domain), a set of operations,

// TODO: template seems better...
// that way we could start with no concept of atoms
// just start playing with ints etc.

template <typename T>
class Atom {
 public:
  Atom(T v) : _value(v) {}
  bool operator==(const Atom<T> &rhs) { return this->_value == rhs._value; }
  Atom(const Atom<T> &rhs) { _value = rhs._value; }
  T value() { return _value; }
  void set(T value) { _value = value; }

 protected:
  T _value;
};

template <class T>
class Set {
 public:
  Set() {}
  int cardinality() { return _universe.size(); }
  void add(T member) { _universe.push_back(member); }
  bool contains(T candidate) {
    for (int i = 0; i < _universe.size(); i++) {
      if (_universe[i] == candidate) return true;
    }
    return false;
  }

 protected:
  std::vector<T> _universe;
};

int main(void) {
  Set<Atom<int>> s;
  int datum = 3;
  s.add(Atom<int>(datum));
  std::cout << "cadrinality of s: " << s.cardinality() << std::endl;
  std::cout << "s.contains(datum): " << s.contains(datum) << std::endl;
  return 0;
}
