#pragma once

namespace Util {
struct Date_ {
  int year;
  int month;
  int date;
  // sunday == 0?
  // enum?
  int day_of_week;
  void roll_day_of_week() {
    ++day_of_week;
    if (day_of_week > 7) {
      day_of_week = 1;
    }
  }
};

class DateUtil {
 public:
  static bool is_leap_year(int);
  static int days_per_month(int, int);
  static void tomorrow(Date_ &);

 protected:
  static int _days_in_months[12];
};

}  // namespace Util
