#include <iostream>
#include <ostream>

#include "gmpxx.h"
#include "int_util.h"

using namespace Util;

/* ---------------------------------------------------
n! means n *  (n - 1) * ... * 3 * 2 * 1.
For example, $10! = 10 * 9 * ... * 3 * 2 * 1 = 3628800
and the sum of the digits in the number 10! is
3 + 6 + 2 + 8 + 8 + 0 + 0 = 27

Find the sum of the digits in the number 100!.
 * ---------------------------------------------------
 */

int main(void) {
  mpz_class sum(0);
  mpz_class f = IntUtil::factorial(100);
  std::string digits = f.get_str();

  for (int i = 0; i < digits.length(); i++) {
    sum += (digits[i] - '0');
  }

  std::cout << "sum: " << std::endl << sum.get_str() << std::endl;
  return 0;
}

/*
gmp::factorial used for result: 648
IntUtil::factorial used for result: 648
OK.

Congratulations, the answer you gave to problem 20 is correct.
You are the 207192nd person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
