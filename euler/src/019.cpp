#include <iostream>
#include <ostream>

#include "date_util.h"

using namespace Util;

/* ---------------------------------------------------
You are given the following information, but you may
prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4,
but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during
the twentieth century (1 Jan 1901 to 31 Dec 2000)?

IOW:
for every day between (1 Jan 1901 to 31 Dec 2000)
if that day is the first of the month
and that day is a Sunday
increment counter.
win.
 * ---------------------------------------------------
 */

bool reached_terminal_date(Date_ d) {
  return d.year >= 2000 && d.month >= 12 && d.date >= 31;
}

int main(void) {
  int start_year = 1901;
  int start_month = 1;
  int start_date = 1;
  // 1 == Monday
  int start_day_of_week = 1;
  unsigned int counter = 0;

  Date_ d{.year = start_year,
          .month = start_month,
          .date = start_date,
          .day_of_week = start_day_of_week};

  while (!reached_terminal_date(d)) {
    if (d.date == 1 && d.day_of_week == 1) {
      ++counter;
    }
    DateUtil::tomorrow(d);
  }

  std::cout << "there are" << std::endl
            << counter << std::endl
            << "first days of the month which are sundays " << std::endl
            << "between 19010101 and 20001231" << std::endl;

  return 0;
}

/*
Congratulations, the answer you gave to problem 19 is correct.
You are the 141588th person to have solved this problem.
This problem has a difficulty rating of 5%.
The highest difficulty rating you have solved remains at 5%.
*/
