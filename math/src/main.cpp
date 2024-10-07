// #include <math.h>

// #include <cmath>
#include <matplot/matplot.h>
#include <matplot/util/colors.h>
#include <matplot/util/common.h>

#include <cmath>
#include <iostream>
#include <set>
#include <vector>
// #include "Eigen/Dense"
// #include "Eigen/src/Core/Matrix.h"

#include "creppl.hpp"

const int N = 15;
const int M = 3;

std::string evaluator(std::vector<CrepplParam> params) {
  // int a, int b, int offset
  int a = params[0].value();
  int b = params[1].value();
  int offset = params[2].value();

  std::string result_beginning = "";
  std::string result_end = "";
  std::vector<int> negatives;
  std::vector<int> positives;
  bool contains_zero = false;

  for (int n = (N / 2) * -1; n <= N / 2; n++) {
    for (int m = (M / 2) * -1; m <= M / 2; m++) {
      int result = (a * n + b * m) - offset;
      if (result == 0) {
        contains_zero = true;
      } else if (result > 0) {
        positives.push_back(result);
      } else {
        negatives.push_back(result);
      }
    }
  }

  // sort them.
  // append them along w/ zero if we saw it.
  sort(positives.begin(), positives.end());
  sort(negatives.begin(), negatives.end());
  // TODO: probably also remove duplicates...

  std::set<int> ps(positives.begin(), positives.end());
  std::set<int> ns(negatives.begin(), negatives.end());
  positives.assign(ps.begin(), ps.end());
  negatives.assign(ns.begin(), ns.end());

  for (int i = 0; i < negatives.size(); i++) {
    result_beginning += ", " + std::to_string(negatives[i]);
  }
  for (int i = 0; i < positives.size(); i++) {
    result_end += ", " + std::to_string(positives[i]);
  }

  result_end += ",...}";
  return "{..." + result_beginning + (contains_zero ? ", 0" : " ") + result_end;
}

std::vector<std::pair<size_t, size_t>> get_edges() {
  return {{0, 0},   {1, 0},   {5, 0},   {0, 1},   {1, 1},   {2, 1},   {6, 1},
          {1, 2},   {2, 2},   {3, 2},   {7, 2},   {2, 3},   {3, 3},   {4, 3},
          {8, 3},   {3, 4},   {4, 4},   {9, 4},   {0, 5},   {5, 5},   {6, 5},
          {10, 5},  {1, 6},   {5, 6},   {6, 6},   {7, 6},   {11, 6},  {2, 7},
          {6, 7},   {7, 7},   {8, 7},   {12, 7},  {3, 8},   {7, 8},   {8, 8},
          {9, 8},   {13, 8},  {4, 9},   {8, 9},   {9, 9},   {14, 9},  {5, 10},
          {10, 10}, {11, 10}, {15, 10}, {6, 11},  {10, 11}, {11, 11}, {12, 11},
          {16, 11}, {7, 12},  {11, 12}, {12, 12}, {13, 12}, {17, 12}, {8, 13},
          {12, 13}, {13, 13}, {14, 13}, {18, 13}, {9, 14},  {13, 14}, {14, 14},
          {19, 14}, {10, 15}, {15, 15}, {16, 15}, {20, 15}, {11, 16}, {15, 16},
          {16, 16}, {17, 16}, {21, 16}, {12, 17}, {16, 17}, {17, 17}, {18, 17},
          {22, 17}, {13, 18}, {17, 18}, {18, 18}, {19, 18}, {23, 18}, {14, 19},
          {18, 19}, {19, 19}, {24, 19}, {15, 20}, {20, 20}, {21, 20}, {25, 20},
          {16, 21}, {20, 21}, {21, 21}, {22, 21}, {26, 21}, {17, 22}, {21, 22},
          {22, 22}, {23, 22}, {27, 22}, {18, 23}, {22, 23}, {23, 23}, {24, 23},
          {28, 23}, {19, 24}, {23, 24}, {24, 24}, {29, 24}, {20, 25}, {25, 25},
          {26, 25}, {35, 25}, {21, 26}, {25, 26}, {26, 26}, {27, 26}, {36, 26},
          {22, 27}, {26, 27}, {27, 27}, {28, 27}, {37, 27}, {23, 28}, {27, 28},
          {28, 28}, {29, 28}, {38, 28}, {24, 29}, {28, 29}, {29, 29}, {30, 29},
          {39, 29}, {29, 30}, {30, 30}, {31, 30}, {40, 30}, {30, 31}, {31, 31},
          {32, 31}, {41, 31}, {31, 32}, {32, 32}, {33, 32}, {42, 32}, {32, 33},
          {33, 33}, {34, 33}, {43, 33}, {33, 34}, {34, 34}, {44, 34}, {25, 35},
          {35, 35}, {36, 35}, {45, 35}, {26, 36}, {35, 36}, {36, 36}, {37, 36},
          {46, 36}, {27, 37}, {36, 37}, {37, 37}, {38, 37}, {47, 37}, {28, 38},
          {37, 38}, {38, 38}, {39, 38}, {48, 38}, {29, 39}, {38, 39}, {39, 39},
          {40, 39}, {49, 39}, {30, 40}, {39, 40}, {40, 40}, {41, 40}, {50, 40},
          {31, 41}, {40, 41}, {41, 41}, {42, 41}, {51, 41}, {32, 42}, {41, 42},
          {42, 42}, {43, 42}, {52, 42}, {33, 43}, {42, 43}, {43, 43}, {44, 43},
          {53, 43}, {34, 44}, {43, 44}, {44, 44}, {54, 44}, {35, 45}, {45, 45},
          {46, 45}, {55, 45}, {36, 46}, {45, 46}, {46, 46}, {47, 46}, {56, 46},
          {37, 47}, {46, 47}, {47, 47}, {48, 47}, {57, 47}, {38, 48}, {47, 48},
          {48, 48}, {49, 48}, {58, 48}, {39, 49}, {48, 49}, {49, 49}, {50, 49},
          {59, 49}, {40, 50}, {49, 50}, {50, 50}, {51, 50}, {60, 50}, {41, 51},
          {50, 51}, {51, 51}, {52, 51}, {61, 51}, {42, 52}, {51, 52}, {52, 52},
          {53, 52}, {62, 52}, {43, 53}, {52, 53}, {53, 53}, {54, 53}, {63, 53},
          {44, 54}, {53, 54}, {54, 54}, {64, 54}, {45, 55}, {55, 55}, {56, 55},
          {65, 55}, {46, 56}, {55, 56}, {56, 56}, {57, 56}, {66, 56}, {47, 57},
          {56, 57}, {57, 57}, {58, 57}, {67, 57}, {48, 58}, {57, 58}, {58, 58},
          {59, 58}, {68, 58}, {49, 59}, {58, 59}, {59, 59}, {60, 59}, {69, 59},
          {50, 60}, {59, 60}, {60, 60}, {61, 60}, {70, 60}, {51, 61}, {60, 61},
          {61, 61}, {62, 61}, {71, 61}, {52, 62}, {61, 62}, {62, 62}, {63, 62},
          {72, 62}, {53, 63}, {62, 63}, {63, 63}, {64, 63}, {73, 63}, {54, 64},
          {63, 64}, {64, 64}, {74, 64}, {55, 65}, {65, 65}, {66, 65}, {56, 66},
          {65, 66}, {66, 66}, {67, 66}, {57, 67}, {66, 67}, {67, 67}, {68, 67},
          {58, 68}, {67, 68}, {68, 68}, {69, 68}, {59, 69}, {68, 69}, {69, 69},
          {70, 69}, {60, 70}, {69, 70}, {70, 70}, {71, 70}, {61, 71}, {70, 71},
          {71, 71}, {72, 71}, {62, 72}, {71, 72}, {72, 72}, {73, 72}, {63, 73},
          {72, 73}, {73, 73}, {74, 73}, {64, 74}, {73, 74}, {74, 74}};
}

int main(int argc, char **argv) {
  std::function<std::string(std::vector<CrepplParam>)> fn = evaluator;

  std::vector<CrepplParam> params{
      CrepplParam("value of a:", CrepplParamType::INT),
      CrepplParam("value of b:", CrepplParamType::INT),
      CrepplParam("    offset:", CrepplParamType::INT),
  };

  // Creppl repl(fn, params);
  // repl.run();

  // plot something...
  using namespace matplot;
  // auto edges = get_edges();
  // graph(edges);

  // fplot("x^2", "o-r")->line_width(2);
  // hold(on);
  // fplot([](double x) { return x * x; }, std::array<double, 2>{-10, 10},
  // "x--b")
  //     ->line_width(2);
  // grid(on);
  //
  // show();

  // == domain?
  // or just plot/view parameters?
  // a vector of 100 evenly spaced doubles [0-10]
  auto x = linspace(0, 10);
  std::cout << "linspace len: " << x.size() << std::endl;
  std::vector<double> xs = linspace(-4, 4);
  std::vector<double> ys = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                            11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

  // std::vector<double> actual_ys;

  // for (int i=0;i<xs.size();i++){
  //   double x = xs[i];
  //   double y =
  // }

  xs = {-2.0, -1.75, -1.5, -1.25, -1,   -0.75, -0.5, -0.25, 0,
        0.25, 0.5,   0.75, 1.0,   1.25, 1.5,   1.75, 2.0};
  std::vector<std::vector<double>> actual_ys;

  auto x_foos = linspace(-4.0, 4.0);
  auto y_foos = transform(x, [&](double x) { return (x * x) / 1.f; });
  // auto c = linspace(-4.0, 4.0, x_foos.size());

  // perhaps can regraph with different transforms...
  // scatter(x_foos, y_foos, c);
  // scatter(x_foos, y_foos);
  // hold(on);
  // y_foos = transform(x, [&](double x) { return (x * x) / 2.f; });
  // scatter(x_foos, y_foos);
  // hold(on);
  // y_foos = transform(x, [&](double x) { return (x * x) / 3.f; });
  // scatter(x_foos, y_foos);
  // hold(on);
  // y_foos = transform(x, [&](double x) { return (x * x) / 50.f; });
  // scatter(x_foos, y_foos);
  // grid(on);
  // show();

  // std::vector<double> xs_source = {0, -6, -5, -4, -3, -2, -1,
  //                                  0, 1,  2,  3,  4,  5,  6};
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

  // plot(real_xs, real_ys);
  scatter(real_xs, real_ys);
  show();

  // trying to plot (x, x^2/y) where x is real
  // and y is a positive integer.

  // for (int i = 1; i <= 10; i++) {
  //   double this_x = xs[i];
  //   std::vector<double> these_ys;
  //   for (int y = 1; y <= 10; y++) {
  //     these_ys.push_back((this_x * this_x) / y);
  //   }
  //   actual_ys.push_back(these_ys);
  // }
  //
  // scatter(linspace(-2, 2), actual_ys);
  // show();

  // what are we trying to show?
  // {(x,x^2/y), xeR, yeN}

  // std::cout << "linspace: " << std::endl;
  // for (int i = 0; i < x.size(); i++) {
  //   std::cout << x[i] << std::endl;
  // }

  // auto y = transform(x, [](double x) { return sin(x); });
  // plot(x, y);
  // grid(on);
  // show();

  return 0;
}
