#include <iostream>

#include "int_util.h"

// #include "Eigen/Dense"
// #include "Eigen/src/Core/Matrix.h"

using namespace Util;

/* -------------------
 * Multiples of 3 or 5
 * -------------------
 */
int main(void) {
  int result = 0;
  for (int i = 1; i < 1000; i++) {
    if (IntUtil::is_multiple_of(i, 3) || IntUtil::is_multiple_of(i, 5)) {
      result += i;
    }
  }

  std::cout << "result:\n" << result << std::endl;
  return 0;
}

/*
Congratulations, the answer you gave to problem 1 is correct.
You are the 989427th person to have solved this problem.
This problem has a difficulty rating of 5%. The highest difficulty rating you
had previously solved was 0%. This is a new record. Well done!

Not enough data to determine solve metrics.
*/
