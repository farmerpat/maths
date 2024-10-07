#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
  // e.g. filtering vector...
  std::vector<int> thing = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // odds only...
  // TODO: honestly, this belongs in a utility method
  // that takes a vec by reference and a filter fn...
  thing.erase(std::remove_if(thing.begin(), thing.end(),
                             [](const int &n) { return n == 0 || n % 2 == 0; }),
              thing.end());
  std::cout << "odd things: \n" << std::endl;
  for (auto i : thing) {
    std::cout << i << std::endl;
  }
  return 0;
}
