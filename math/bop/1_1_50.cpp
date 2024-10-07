#include <matplot/matplot.h>
#include <matplot/util/colors.h>
#include <matplot/util/common.h>

#include <cmath>
#include <iostream>
#include <set>
#include <vector>

// trying to plot (x, x^2/y) where x is real
// and y is a positive integer.
int main(int argc, char **argv) {
  using namespace matplot;

  auto xs_source = linspace(-60, 60, 300);
  std::vector<double> real_xs;
  std::vector<double> real_ys;

  for (int k = 1; k < 52; k++) {
    for (int i = 0; i < xs_source.size(); i++) {
      auto this_x = xs_source[i];
      real_xs.push_back(this_x);
      real_ys.push_back((this_x * this_x) / k);
    }
  }

  scatter(real_xs, real_ys);
  show();

  return 0;
}
