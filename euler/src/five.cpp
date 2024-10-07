#include <iostream>
#include <vector>

#include "int_util.h"

using namespace Util;

bool divided_by_all(int n, std::vector<int> all) {
  for (auto a : all) {
    if (!divides(a, n)) {
      return false;
    }
  }
  return true;
}

/* ----------------------------------------------------
2520 is the smallest number that can be divided by
each of the numbers from 1 to 10 without any remainder.
What is the smallest positive number that is evenly
divisible by all of the numbers from 1 to 20?
 * ----------------------------------------------------
 */
int main(void) {
  std::vector<int> divisors;
  for (int i = 1; i <= 20; i++) {
    divisors.push_back(i);
  }

  int magick_number = 0;

  for (int i = 20;; i++) {
    if (divided_by_all(i, divisors)) {
      magick_number = i;
      break;
    }
  }

  std::cout << "The smallest positive number that is evenly "
            << "divisible by each of [1..20] is:" << std::endl
            << magick_number << std::endl;

  return 0;
}

/*
Congratulations, the answer you gave to problem 5 is correct.
You are the 506111th person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
