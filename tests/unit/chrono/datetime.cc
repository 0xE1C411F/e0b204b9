#include "chrono/datetime.h"
#include "helpers/comparisons.h"
#include "helpers/test_session.h"

double DURATION_TOLERANCE = (double)0.001 / chrono::MILLISECONDS_IN_DAY;
bool datetime_valid_initialisation() {
  [[maybe_unused]] chrono::datetime d1{};
  [[maybe_unused]] chrono::datetime d2{2020, 1, 1};
  [[maybe_unused]] chrono::datetime d3{2020, 1, 1, 14, 0, 30, 256};
  return true;
}

bool datetime_invalid_day() {
  try {
    [[maybe_unused]] chrono::datetime d3{2020, 2, 40};
  } catch (std::invalid_argument const& ex) {
    return true;
  }
  return false;
}

bool leap_years() {
  bool passed = chrono::is_leap(2000);
  passed = passed && !chrono::is_leap(2001);
  passed = passed && !chrono::is_leap(2002);
  passed = passed && !chrono::is_leap(2003);
  passed = passed && chrono::is_leap(2004);
  passed = passed && !chrono::is_leap(2005);
  passed = passed && chrono::is_leap(2008);
  passed = passed && chrono::is_leap(2096);
  passed = passed && !chrono::is_leap(2099);
  passed = passed && !chrono::is_leap(2100);
  passed = passed && !chrono::is_leap(2200);
  passed = passed && !chrono::is_leap(2300);
  passed = passed && chrono::is_leap(2304);
  return passed && chrono::is_leap(2400);
}

bool last_days() {
  bool passed = chrono::last_day_of_month(1) == 31;
  passed = passed && (chrono::last_day_of_month(2) == 28);
  passed = passed && (chrono::last_day_of_month(3) == 31);
  passed = passed && (chrono::last_day_of_month(4) == 30);
  passed = passed && (chrono::last_day_of_month(5) == 31);
  passed = passed && (chrono::last_day_of_month(6) == 30);
  passed = passed && (chrono::last_day_of_month(7) == 31);
  passed = passed && (chrono::last_day_of_month(8) == 31);
  passed = passed && (chrono::last_day_of_month(9) == 30);
  passed = passed && (chrono::last_day_of_month(10) == 31);
  passed = passed && (chrono::last_day_of_month(11) == 30);
  passed = passed && (chrono::last_day_of_month(12) == 31);

  passed = passed && (chrono::last_day_of_month(1, 1996) == 31);
  passed = passed && (chrono::last_day_of_month(2, 1996) == 29);
  passed = passed && (chrono::last_day_of_month(3, 1996) == 31);
  passed = passed && (chrono::last_day_of_month(4, 1996) == 30);
  passed = passed && (chrono::last_day_of_month(5, 1996) == 31);
  passed = passed && (chrono::last_day_of_month(6, 1996) == 30);
  passed = passed && (chrono::last_day_of_month(7, 1996) == 31);
  passed = passed && (chrono::last_day_of_month(8, 1996) == 31);
  passed = passed && (chrono::last_day_of_month(9, 1996) == 30);
  passed = passed && (chrono::last_day_of_month(10, 1996) == 31);
  passed = passed && (chrono::last_day_of_month(11, 1996) == 30);
  return passed && (chrono::last_day_of_month(12, 1996) == 31);
}

bool serial_to_civil_date_inversion() {
  chrono::datetime d1{738'725, 3'723'004};
  const auto [year, month, day] = d1.civil_date();
  const auto [hour, minute, second, millisecond] = d1.time();
  bool passed = (year == 2022) && (month == 9) && (day == 22) && (hour == 1) && (minute == 2) && (second == 3) &&
                (millisecond == 4);
  chrono::datetime d2{2022, 9, 22, 1, 2, 3, 4};
  return passed && (d1 == d2);
}

bool comparison() {
  chrono::datetime d1{2000, 1, 1};
  chrono::datetime d2{1999, 12, 31};
  bool passed = (d1 != d2) && (d1 > d2) && (d1 >= d2);
  chrono::datetime d3{2000, 1, 1, 0, 0, 1, 23};
  chrono::datetime d4{2000, 1, 1, 0, 0, 1, 24};
  passed = passed && (d3 < d4) && (d3 <= d4);
  chrono::datetime d5{2000, 1, 1, 0, 0, 1, 23};
  chrono::datetime d6{2000, 1, 1, 0, 0, 1, 23};
  return passed && (d5 == d6) && (d5 >= d6) && (d5 <= d6);
}

bool arithmetics() {
  chrono::datetime x{2000, 1, 1, 23, 59, 59, 999};
  chrono::datetime y{2000, 1, 2};
  bool passed = helpers::is_double_equal(x - y, -(double)1 / chrono::MILLISECONDS_IN_DAY, DURATION_TOLERANCE);

  passed = passed && helpers::is_double_equal(y - x, (double)1 / chrono::MILLISECONDS_IN_DAY, DURATION_TOLERANCE);
  chrono::datetime z{2001, 1, 1, 23, 59, 59, 999};
  passed = passed && helpers::is_double_equal(z - x, (double)366.0, DURATION_TOLERANCE);
  passed = passed && ((z - 366) == x) && ((x + 366) == z);
  return passed;
};

int main() {
  return helpers::run_test_session({
      TEST_FUNCTION(datetime_invalid_day),
      TEST_FUNCTION(datetime_valid_initialisation),
      TEST_FUNCTION(leap_years),
      TEST_FUNCTION(last_days),
      TEST_FUNCTION(serial_to_civil_date_inversion),
      TEST_FUNCTION(comparison),
      TEST_FUNCTION(arithmetics),
  });
}
