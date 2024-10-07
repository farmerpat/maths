#include <iostream>

#include "int_util.h"

using namespace Util;

/* --------------------------------------------------
Find the difference between the sum of the squares of
the first one hundred natural numbers and the square
of the sum.
 * --------------------------------------------------
 */
int main(void) {
  long result = 0;
  long n = 100;
  long sq_of_sums = IntUtil::square_of_sums(n);
  long sum_of_sqs = IntUtil::sum_of_squares(n);

  std::cout << "The difference between the sum of the squares of "
            << "the first one hundred natural numbers and the the "
            << "square of the sum is " << sq_of_sums - sum_of_sqs << std::endl;
  return 0;
}

/*
Congratulations, the answer you gave to problem 6 is correct.
You are the 509347th person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
