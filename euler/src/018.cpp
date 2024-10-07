#include <iostream>
#include <ostream>
#include <vector>

/* --------------------------------------------------
By starting at the top of the triangle below and
moving to adjacent numbers on the row below, the
maximum total from top to bottom is 23
3
7 4
2 4 6
8 5 9 3

Then the two adjacent choices available to the current
number in the pyramid are twofold, both being in the
row below. They are the element below with the same
index; and the elt below with index+1 if it exists.

That is, 3 + 7 + 4 + 9 = 23

Find the maximum total from top to bottom of the triangle below:

75
95 64
17 47 82
18 35 87 10
20 04 82 47 65
19 01 23 75 03 34
88 02 77 73 07 63 67
99 65 04 28 06 16 70 92
41 41 26 56 83 40 80 70 33
41 48 72 33 47 32 37 16 94 29
53 71 44 65 25 43 91 52 97 51 14
70 11 33 28 77 73 17 78 39 68 17 57
91 71 52 38 17 14 91 43 58 50 27 29 48
63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

NOTE: As there are only 16384 routes, it is possible
to solve this problem by trying every route. However,
Problem 67 is the same challenge with a triangle
containing one-hundred rows; it cannot be solved by
brute force, and requires a clever method!
 * --------------------------------------------------
 */

#define TRIANGLE_SIZE 15
// NOTE: Could construct TRIANGLE_SIZE dynamically. Worth?
static int TRIANGLE_SIZES[] = {1, 2,  3,  4,  5,  6,  7, 8,
                               9, 10, 11, 12, 13, 14, 15};
static std::vector<std::vector<int>> TRIANGLE = {
    {75},
    {95, 64},
    {17, 47, 82},
    {18, 35, 87, 10},
    {20, 04, 82, 47, 65},
    {19, 01, 23, 75, 03, 34},
    {88, 02, 77, 73, 07, 63, 67},
    {99, 65, 04, 28, 06, 16, 70, 92},
    {41, 41, 26, 56, 83, 40, 80, 70, 33},
    {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
    {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
    {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
    {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
    {63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
    {04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 04, 23}};

int main(void) {
  bool first_time = true;
  unsigned long result = 0;
  int candidate = 0;
  int current_number = TRIANGLE[0][0];
  result += current_number;
  int candidate_one = 0;
  int candidate_two = 0;
  int column_pos = 0;

  for (int row = 1; row < TRIANGLE_SIZE; ++row) {
    std::vector<int> this_row = TRIANGLE[row];
    candidate_one = this_row[column_pos];
    if (column_pos + 1 < this_row.size()) {
      candidate_two = this_row[column_pos + 1];
    } else {
      candidate_two = 0;
    }

    // NOTE: possible failure in cases where the candidates are the same,
    // since choosing one over the other may result in greater future
    // magnitude.
    // TODO: may need to peek further into the future if so.
    if (candidate_one > candidate_two) {
      current_number = candidate_one;
    } else {
      current_number = candidate_two;
      ++column_pos;
    }

    // std::cout << "result prior: " << result << std::endl;
    result += current_number;
    // std::cout << "result after: " << result << std::endl;
  }

  std::cout << "All done." << std::endl << result << std::endl;
  return 0;
}

/*
1064 is incorrect.
...
I attained the same result by manually tracing my algorithm through
the given dataset.
Probably looking ahead only one row is insufficient.
If so, we need a better way...
They've explicated that brute force isn't viable when the number
of rows grows sufficiently large...
Keep thinking.
Let it cook.

Perhaps the notion of sub-triangles comes into play.
Let it cook.

Consider also starting from the bottom...
*/
