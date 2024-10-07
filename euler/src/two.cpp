#include <iostream>
#include <vector>

#include "int_util.h"

using namespace Util;

/* --------------------------------------------------
 * By considering the terms in the Fibonacci sequence
 * whose values do not exceed four million, find the
 * sum of the even-valued terms.
 * --------------------------------------------------
 */
int main(void) {
  int result = 0;
  int fib_counter = 0;
  int this_fib = 0;
  std::vector<int> fibs;

  std::cout << "Generating fibs..." << std::endl;
  for (;;) {
    this_fib = IntUtil::fibonacci(fib_counter);
    fib_counter++;
    if (this_fib > 4000000) {
      break;
    }
    fibs.push_back(this_fib);
  }

  std::cout << "Summing fibs..." << std::endl;
  for (int i = 0; i < fibs.size(); i++) {
    // if its even, add it to the result.
    this_fib = fibs[i];
    if (IntUtil::is_even(this_fib)) {
      result += this_fib;
    }
  }

  std::cout << "result:\n" << result << std::endl;
  return 0;
}

/*
Congratulations, the answer you gave to problem 2 is correct.
You are the 789234th person to have solved this problem.

This problem has a difficulty rating of 5%. The highest
difficulty rating you have solved remains at 5%.

Not enough data to determine solve metrics.
*/
