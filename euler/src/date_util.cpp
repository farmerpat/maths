#include "date_util.h"

namespace Util {
int DateUtil::_days_in_months[12] = {31, 28, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31};

bool DateUtil::is_leap_year(int y) {
  if (y % 4 == 0) {
    if (y % 100 == 0) {
      if (y % 400 == 0) {
        return true;
      }
      return false;
    }
    return true;
  }

  return false;
}

int DateUtil::days_per_month(int y, int m) {
  if (!(0 < m && m < 13) || y < 1) {
    return 0;
  }

  if (m != 2) {
    return _days_in_months[m - 1];
  } else {
    if (is_leap_year(y)) {
      return _days_in_months[m - 1] + 1;
    } else {
      return _days_in_months[m - 1];
    }
  }
}

// update the struct to contain the representation of tomorrow.
void DateUtil::tomorrow(Date_ &date) {
  // NOTE:it wouldn't surprise me if it turned out that we need
  // to return tomorrow. e.g. may need to compare today and
  // tomorrow etc.

  if (date.month == 2) {
    // possible leap year things
    // TODO: reduntant.
    // probably simplify.
    if (date.date + 1 <= days_per_month(date.year, date.month)) {
      ++date.date;
      date.roll_day_of_week();
    } else {
      date.date = 1;
      ++date.month;
      date.roll_day_of_week();
    }
  } else {
    // simplest case. update the date, roll day of week. done.
    if (date.date + 1 <= days_per_month(date.year, date.month)) {
      ++date.date;
      date.roll_day_of_week();
    } else {
      // otherwise, it's the next month
      if (date.month == 12) {
        date.month = 1;
        ++date.year;
        date.date = 1;
        date.roll_day_of_week();
      } else {
        ++date.month;
        date.date = 1;
        date.roll_day_of_week();
      }
    }
    // in english:
    // if .date+1 <= number of days in the month
    // (a function like days_per_month(d.year, d.month)
    // would be useful here.)
    // just increment date.
    // if .date+1 > #days in month
    // we have to increment the month also.
    // and if we are incrementing the month
    // then we may need to increment the year.
  }
}

}  // namespace Util
