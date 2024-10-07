#include <iostream>
#include <ostream>

#include "int_util.h"

using namespace Util;

/* -------------------------------------------------
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17
Find the sum of all the primes below two million.
 * ------------------------------------------------
 */
int main(void) {
  int target = 2000000;
  long result = 0;

  std::vector<long> primes = IntUtil::primes_below(target);

  for (int i = 0; i < primes.size(); i++) {
    result += primes[i];
  }

  std::cout << "The sum of all primes below " << target << " are: " << std::endl
            << result << std::endl;
  return 0;
}

/*
Congratulations, the answer you gave to problem 10 is correct.
You are the 340108th person to have solved this problem.

You have earned 1 new award:
Decathlete: Solve ten consecutive problems

This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
