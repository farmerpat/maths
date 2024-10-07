#include <iostream>
#include <vector>
#include <ranges>
#include <format>

typedef unsigned long long ull;

class PrimeFactor {
  public:
    PrimeFactor(ull prime, ull power) : _prime(prime), _power(power) {}
    ull prime() { return _prime; };
    ull power() { return _power; };

  protected:
    ull _prime;
    ull _power;
};

class Number {
  public:
    Number(ull number, std::vector<PrimeFactor> pfs)
      : _number(number), _pfs(pfs) {}
    ull raw() { return _number; };
    std::vector<PrimeFactor> pfs() { return _pfs; };

  protected:
    ull _number;
    std::vector<PrimeFactor> _pfs;
};

int main(void) {
  std::vector<Number> numbers;
  numbers.push_back(Number(1, {PrimeFactor(1, 1)}));
  numbers.push_back(Number(2, {PrimeFactor(2, 1)}));
  numbers.push_back(Number(3, {PrimeFactor(3, 1)}));
  numbers.push_back(Number(4, {PrimeFactor(2, 2)}));
  numbers.push_back(Number(5, {PrimeFactor(5, 1)}));
  numbers.push_back(Number(6, {PrimeFactor(2, 1), PrimeFactor(3, 1)}));
  numbers.push_back(Number(7, {PrimeFactor(7, 1)}));
  numbers.push_back(Number(8, {PrimeFactor(2, 3)}));
  numbers.push_back(Number(9, {PrimeFactor(3, 2)}));
  numbers.push_back(Number(10, {PrimeFactor(2, 1), PrimeFactor(5,1)}));

  for (int i = 0; i < numbers.size(); i++) {
    Number n = numbers[i];
    std::cout << n.raw() << ": ";
    auto fs = n.pfs();
    for (int j = 0; j < fs.size(); j++) {
      auto this_pf = fs[j];
      std::cout << this_pf.prime() << "^" << this_pf.power()
        << (j == fs.size() - 1 ? "" : ", ");
    }

  }

  auto const ints = {0, 1, 2, 3, 4, 5};
  auto even = [](int i) { return 0 == i % 2; };
  auto square = [](int i) { return i * i; };

  // the "pipe" syntax of composing the views:
  // TODO: benchmark this functional style for hard problems...
  // if it's viable, go for it!
  for (int i : ints | std::views::filter(even) | std::views::transform(square))
    std::cout << i << ' ';

  std::cout << '\n';
  return 0;
}

