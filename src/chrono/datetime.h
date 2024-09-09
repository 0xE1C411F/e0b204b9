#ifndef CHRONO_DATETIME_H_
#define CHRONO_DATETIME_H_

#include <iostream>
#include <tuple>

namespace chrono {
constexpr int DAYS_IN_ERA = 146'097;
constexpr int MILLISECONDS_IN_DAY = 86'400'000;

/**
 * Datetime object with milliseconds-precision
 *
 * The implementation is based on the paper by Howard Hinnant on designing a chrono-compatible date library
 * (howardhinnant.github.io/date_algorithms.html), although this class does not implement chrono-compatibility.
 */
class datetime {
 private:
  /* the internal representation of a datetime is two ints, one for the date and one for the time */
  int serial_date{0};
  int time_ms{0};

 public:
  /**
   * Construct a datetime object from a civil calendar representation
   */
  datetime(int year = 2000,
           int month = 1,
           int day = 1,
           int hour = 0,
           int minute = 0,
           int second = 0,
           int millisecond = 0);
  /**
   * Extract the civil date in tuple(year, month, day) format
   */
  constexpr std::tuple<int, int, int> civil_date() const noexcept;

  /**
   * Subtract two datetimes to get the number of days
   */
  friend constexpr double operator-(const datetime& left_hand_side, const datetime& right_hand_side) noexcept;
};

/**
 * Return true if the year is a leap year
 */
constexpr bool is_leap(int year) noexcept;

/**
 * Return last day of month (both month and day starting at 1)
 */
constexpr int last_day_of_month(int month, int year = 1) noexcept;
}  // namespace chrono

/**
 * Display datetime
 */
constexpr std::ostream& operator<<(std::ostream& ostream, const chrono::datetime& datetime);

#endif
