#include <iostream>
#include <ostream>

#include "int_util.h"

using namespace Util;

/* --------------------------------------------------------
Lattice Paths.
Starting in the top left corner of a 2x2 grid, and only
being able to move to the right and down, there are exactly
6 routes to the bottom right corner. How many such routes
are there through a 20x20 grid?
 * --------------------------------------------------------
 */
static unsigned long long success_count = 0;
static const int MAX_COL = 20;
static const int MAX_ROW = 20;

void walkabout(int x, int y) {
  if (x == MAX_COL && y == MAX_ROW) {
    success_count++;
    return;
  }

  // if can move right, do it.
  if ((x + 1) <= MAX_COL) {
    walkabout(x + 1, y);
  }

  // also if can move down, do it.
  if ((y + 1) <= MAX_ROW) {
    walkabout(x, y + 1);
  }
}

// NOTE:
// maybe try keeping a 2d array of state
// if rollover (again!) wasn't the issue...
// but my answers for 2x2, 3x3, and 4x4
// are correct.
int main(void) {
  walkabout(0, 0);

  std::cout << "Total successful routes: " << std::endl
            << success_count << std::endl;

  return 0;
}

// first result was failure:
// Total successful routes:
// 407575348

// after possible rollover fix (int -> unsigned long long):
// 137846528820

/*
Congratulations, the answer you gave to problem 15 is correct.
You are the 195762nd person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
