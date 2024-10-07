#include <iostream>
#include <vector>

#include "int_util.h"

using namespace Util;

struct PalindromeProduct {
  int x;
  int y;
  int palindrome;
};

/* ---------------------------------------------------
  A palindromic number reads the same both ways.
  The largest palindrome made from the product of two
  2-digit numbers is 9009 = 91 * 99
  Find the largest palindrome made from the product of
  two 3-digit numbers.
 * ---------------------------------------------------
 */
int main(void) {
  std::vector<PalindromeProduct> palindromes;

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      int maybe_palindrome = i * j;

      if (IntUtil::is_palindrome(maybe_palindrome)) {
        struct PalindromeProduct p = {
            .x = i, .y = j, .palindrome = maybe_palindrome};
        palindromes.push_back(p);
      }
    }
  }

  // TODO: maybe there's a cleaner way...
  struct PalindromeProduct max = {.x = 0, .y = 0, .palindrome = 0};
  for (int i = 0; i < palindromes.size(); i++) {
    auto candidate = palindromes[i];
    if (candidate.palindrome > max.palindrome) {
      max.x = candidate.x;
      max.y = candidate.y;
      max.palindrome = candidate.palindrome;
    }
  }

  std::cout << "the largest palindrome which is a product of two "
            << "3-digit numbers is " << max.palindrome << std::endl
            << ", which is the product "
            << "of " << max.x << " and " << max.y << std::endl;
  return 0;
}

/*
Congratulations, the answer you gave to problem 4 is correct.
You are the 503103rd person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.

Not enough data to determine solve metrics.
*/
