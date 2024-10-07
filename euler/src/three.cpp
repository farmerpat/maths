#include <algorithm>
#include <iostream>
#include <vector>

#include "int_util.h"

using namespace Util;

/* --------------------------------------------------
The prime factors of 13195 are 5, 7, 13 and 29
What is the largest prime factor of the number
600851475143?
 * --------------------------------------------------
 */
int main(void) {
  long int n = 600851475143;
  std::vector<long int> factors;
  std::cout << "getting factors..." << std::endl;
  // this is too bloody slow for my speed.
  // factors = IntUtil::factors(n);
  // std::cout << "filtering primes..." << std::endl;
  // IntUtil::rm_if(factors, [](const long &n) { return !IntUtil::is_prime(n);
  // }); std::cout << "finding maximum..." << std::endl; int
  // largest_prime_factor =
  //     *(std::max_element(std::begin(factors), std::end(factors)));
  // std::cout << "max PF:\n" << largest_prime_factor << std::endl;

  // it's not even.
  // it has itself and 1 as factors.
  // let's get the rest
  for (long i = 3; i < n; i += 2) {
    // if (i % 729 == 0) {
    // if (i % 531441 == 0) {
    if (i % 1594323 == 0) {
      std::cout << i << "/" << n << std::endl;
    }

    if (divides(i, n)) {
      if (IntUtil::is_prime(i)) {
        factors.push_back(i);
      }
    }
  }

  long largest_prime_factor =
      *(std::max_element(std::begin(factors), std::end(factors)));
  std::cout << "max PF:\n" << largest_prime_factor << std::endl;

  return 0;
}

/*
Congratulations, the answer you gave to problem 3 is correct.
You are the 568514th person to have solved this problem.

You have earned 1 new award:
  Baby Steps: Solve three problems

This problem has a difficulty rating of 5%. The highest difficulty
rating you have solved remains at 5%.

Not enough data to determine solve metrics.
*/
