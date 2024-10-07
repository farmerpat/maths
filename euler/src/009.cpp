#include <iostream>
#include <ostream>

#include "int_util.h"

using namespace Util;

/* ------------------------------------------------
 * A Pythagorean triplet is a set of three natural
 * numbers, a < b < c, for which, a^2 + b^2 = c^2.
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
 * There exists exactly one Pythagorean triplet for
 * which a + b + c = 1000. Find the product abc.
 * ------------------------------------------------
 */
int main(void) {
  Triplet result;
  std::vector<Triplet> results;
  int target = 1001;
  results = IntUtil::get_all_pythagorean_triplets_before(target);

  for (int i = 0; i < results.size(); i++) {
    Triplet trip = results[i];
    if ((trip.a + trip.b + trip.c) == 1000) {
      result = trip;
    }
  }

  std::cout << "The triplet whose elements sum to 1000 is: " << result.a << ", "
            << result.b << ", " << result.c << std::endl
            << "The product of the elements is "
            << result.a * result.b * result.c << std::endl;
  return 0;
}

/*
Congratulations, the answer you gave to problem 9 is correct.
You are the 370744th person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
