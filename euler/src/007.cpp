#include <iostream>
#include <ostream>

#include "int_util.h"

using namespace Util;

/* --------------------------------------------------
 * The sixth prime number is 13.
 * What is the 10001th prime number?
 * --------------------------------------------------
 */
int main(void) {
  long n = 10001;
  long result = IntUtil::nth_prime(n);
  std::cout << "the " << n << "th prime is \n" << result << std::endl;

  return 0;
}

/*
Congratulations, the answer you gave to problem 7 is correct.
You are the 436013th person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
