#pragma once
#include <functional>
#include <vector>

namespace Util {

template <typename T>
inline T reduce(std::vector<T> v, std::function<T(T, T)> &lambda, T collector) {
  T result = collector;
  for (unsigned long int i = 0; i < v.size(); i++) {
    result = lambda(result, v[i]);
  }

  return result;
}
}  // namespace Util
