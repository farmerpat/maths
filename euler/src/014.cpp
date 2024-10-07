#include <iostream>
#include <ostream>

#include "int_util.h"

using namespace Util;

/* -------------------------------------------------------
The following iterative sequence is defined for the set of
positive integers:
n -> n/2 if (n is even)
n -> 3n + 1 if (n is odd)

Using the rule above and starting with 13,
we generate the following sequence:
13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -. 1.

It can be seen that this sequence (starting at 13 and
finishing at 1) contains 10 terms. Although it has not
been proved yet (Collatz Problem), it is thought that all
starting numbers finish at 1.

Which starting number, under one million, produces the
longest chain?

NOTE: Once the chain starts the terms are allowed to go
above one million.
 * ---------------------------------------------------------
 */
int main(void) {
  long seed = 0;
  long chain_length;
  long max_chain_length = 0;
  long producer_of_chain;
  std::vector<long> seq;

  for (long i = 1; i < 1000000; i++) {
    seq = IntUtil::collatz_seq(i);
    chain_length = seq.size();
    if (chain_length > max_chain_length) {
      max_chain_length = chain_length;
      seed = i;
    }
  }

  std::cout
      << "The Collatz seed under 1,000,000 which produces the longest chain is "
      << std::endl
      << seed << std::endl
      << "The length of the chain is " << max_chain_length << std::endl;

  return 0;
}

/*
Congratulations, the answer you gave to problem 14 is correct.
You are the 236862nd person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
