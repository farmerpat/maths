#include <iostream>
#include <ostream>

#include "gmp.h"
#include "gmpxx.h"

/* -----------------------------------------------
2^15 = 32768 and the sum of its digits is:
3 + 2 + 7 + 6 + 8 = 26

What is the sum of the digits of the number 2^1000
 * -----------------------------------------------
 */
int main(void) {
  unsigned long exponent = 1000;
  unsigned long base = 2;
  mpz_class summation_result(0);
  mpz_class result(0);
  mpz_ui_pow_ui(result.get_mpz_t(), base, exponent);

  std::string digits = result.get_str();

  for (int i = 0; i < digits.length(); i++) {
    summation_result += (digits[i] - '0');
  }

  std::cout << summation_result.get_str() << std::endl;
  return 0;
}

/*
bignum: 1366
gmp: 1366

Congratulations, the answer you gave to problem 16 is correct.
You are the 239042nd person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
