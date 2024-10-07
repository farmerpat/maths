#include <iostream>
#include <ostream>

#include "f_util.h"
#include "gmpxx.h"
#include "int_util.h"

using namespace Util;

/* -----------------------------------------------------
Let d(n) be defined as the sum of proper divisors of n
(numbers less than n which divide evenly into n).

If d(a) = b and d(b) = a, where a ~= b, then a and b
are an amicable pair and each of a and b are called
amicable numbers.

For example, the proper divisors of 220 are
1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110;
therefore d(220) = 284.
The proper divisors of 284 are 1, 2, 4, 71 and 142;
so d(284) = 220.
Evaluate the sum of all the amicable numbers under 10000
 * -----------------------------------------------------
 */

// Evaluate the sum of all the amicable numbers under 10000
int main(void) {
  // mpz_class result(0);
  std::vector<unsigned long> amicables;
  unsigned long N = 10000;
  // unsigned long N = 1000;

  // TODO:? surely there is a less naive approach...
  for (unsigned long i = 2; i <= N; i++) {
    if (i % 100 == 0) {
      std::cout << "processing " << i << std::endl;
    }

    // TODO: naievly, each integer below i is a candidate...
    // yet brute force takes longer than 1minute to run.
    // probably once the sum of j's divisors exceed i's,
    // we can continue. I wonder also if evenness and oddness have to do with
    // amicability.
    for (unsigned long j = 1; j <= i; j++) {
      if (i != j && IntUtil::are_amicable(i, j)) {
        amicables.push_back(i);
        amicables.push_back(j);
      }
    }
  }

  std::cout << "amicables: " << std::endl;
  for (int i = 0; i < amicables.size(); i++) {
    std::cout << amicables[i] << std::endl;
  }

  std::function<unsigned long(unsigned long, unsigned long)> adder =
      [](unsigned long a, unsigned long b) -> unsigned long { return a + b; };

  unsigned long result = reduce(amicables, adder, (unsigned long)0);

  std::cout << "result: " << std::endl;
  std::cout << result << std::endl;

  return 0;
}

/*
naive: 31626

Congratulations, the answer you gave to problem 21 is correct.
You are the 153776th person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
