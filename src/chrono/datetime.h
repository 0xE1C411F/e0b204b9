#ifndef CHRONO_DATETIME_H_
#define CHRONO_DATETIME_H_

#include <iomanip>
#include <iostream>
#include <tuple>
#include "core/exceptions.h"

namespace chrono {
constexpr int DAYS_IN_ERA = 146'097;
constexpr int MILLISECONDS_IN_DAY = 86'400'000;

/**
 * Return true if the year is a leap year
 */
constexpr bool is_leap(int year) noexcept {
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

/**
 * Return last day of month (both month and day starting at 1)
 */
constexpr int last_day_of_month(int month, int year = 1) noexcept {
  constexpr unsigned char days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return (month != 2 || !is_leap(year)) ? days[month - 1] : 29;
}

/**
 * Datetime object with milliseconds-precision
 *
 * The implementation is based on the paper by Howard Hinnant on designing a chrono-compatible date library
 * (howardhinnant.github.io/date_algorithms.html), although this class does not implement chrono-compatibility.
 */
class datetime {
 private:
  /* the internal representation of a datetime is two ints, one for the date and one for the time */
  int serial_date;
  int time_ms;

 public:
  constexpr datetime(int serial_date = 0, int time_ms = 0) : serial_date{serial_date}, time_ms{time_ms} {};
  /**
   * Construct a datetime object from a civil calendar representation
   */
  constexpr datetime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0)
      : serial_date{0}, time_ms{0} {
    core::require((year >= 0) && (year <= 100'000), "year is not in valid range [0, 100'000]");
    core::require((month >= 1) && (month <= 12), "month is not in valid range [1, 12]");
    const int max_day = last_day_of_month(month, year);
    core::require((day >= 1) && (day <= max_day), "day is not in valid range [1, month-specific]");
    core::require((hour >= 0) & (hour < 24), "hour is not in valid range [0, 24)");
    core::require((minute >= 0) && (minute < 60), "minute is not in valid range [0, 60)");
    core::require((second >= 0) && (second < 60), "second is not in valid range [0, 60)");
    core::require((millisecond >= 0) && (millisecond < 1'000), "millisecond is not in valid range [0, 1'000)");

    /* date conversion (days_from_civil) */
    year -= month <= 2;                  /* the year starts on march 1st, allowing the leap day to be the last */
    const int standard_era = year / 400; /* the gregorian calendar has eras of 400 years */
    const int year_of_standard_era = year - standard_era * 400;

    /* month is converted in a standard month, the 153 x + 2 / 5 takes advantage of rounding to get the correct number
     * of days for each month (note that this is possible because of having placed february 29th as the last day of the
     * year
     */
    const int day_of_year = (153 * (month > 2 ? month - 3 : month + 9) + 2) / 5 + day - 1;

    const int day_of_standard_era =
        year_of_standard_era * 365 + year_of_standard_era / 4 - year_of_standard_era / 100 + day_of_year;

    serial_date = standard_era * DAYS_IN_ERA + day_of_standard_era;
    time_ms = hour * 3'600'000 + minute * 60'000 + second * 1'000 + millisecond;
  };

  /**
   * Extract the civil date in tuple(year, month, day) format
   */
  constexpr std::tuple<int, int, int> civil_date() const noexcept {
    const int standard_era = serial_date / DAYS_IN_ERA;
    const int day_of_standard_era = serial_date - standard_era * DAYS_IN_ERA;
    const int year_of_standard_era =
        (day_of_standard_era - day_of_standard_era / (4 * 365 + 1) + day_of_standard_era / (100 * 365 + 25 - 1) -
         day_of_standard_era / (DAYS_IN_ERA - 1)) /
        365;

    const int day_of_year =
        day_of_standard_era - (365 * year_of_standard_era + year_of_standard_era / 4 - year_of_standard_era / 100);
    const int standard_month = (5 * day_of_year + 2) / 153;
    const int civil_day = day_of_year - (153 * standard_month + 2) / 5 + 1;
    const int civil_month = standard_month < 10 ? standard_month + 3 : standard_month - 9;
    const int civil_year = year_of_standard_era + standard_era * 400 + (civil_month <= 2);

    return std::tuple<int, int, int>{civil_year, civil_month, civil_day};
  }
  /**
   * Extract the time of day (24h) in tuple(hour, minute, second, millisecond) format
   */
  constexpr std::tuple<int, int, int, int> time() const noexcept {
    int hour = time_ms / (60 * 60 * 1'000);

    int remainder = time_ms % (60 * 60 * 1'000);
    int minute = remainder / (60 * 1'000);

    remainder %= (60 * 1'000);
    int second = remainder / 1'000;

    remainder %= 1'000;

    return std::make_tuple(hour, minute, second, remainder);
  }

  /**
   * Subtract two datetimes to get the number of days
   */
  friend constexpr double operator-(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
    return left_hand_side.serial_date - right_hand_side.serial_date +
           (left_hand_side.time_ms - right_hand_side.time_ms) / (double)MILLISECONDS_IN_DAY;
  };

  /**
   * Add n days to datetime
   */
  friend constexpr datetime operator+(const datetime& left_hand_side, int right_hand_side) noexcept {
    return datetime{left_hand_side.serial_date + right_hand_side, left_hand_side.time_ms};
  };
  /**
   * Add n days to datetime
   */
  friend constexpr datetime operator+(int left_hand_side, const datetime& right_hand_side) noexcept {
    return right_hand_side + left_hand_side;
  };

  /**
   * Subtract n days from datetime
   */
  friend constexpr datetime operator-(const datetime& left_hand_side, int right_hand_side) noexcept {
    return datetime{left_hand_side.serial_date - right_hand_side, left_hand_side.time_ms};
  };

  /**
   * Compare datetimes
   */
  friend constexpr bool operator==(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
    return (left_hand_side.serial_date == right_hand_side.serial_date) &&
           (left_hand_side.time_ms == right_hand_side.time_ms);
  };
  friend constexpr bool operator!=(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
    return !(left_hand_side == right_hand_side);
  };
  friend constexpr bool operator>=(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
    return (left_hand_side.serial_date > right_hand_side.serial_date) ||
           ((left_hand_side.serial_date == right_hand_side.serial_date) &&
            (left_hand_side.time_ms >= right_hand_side.time_ms));
  };
  friend constexpr bool operator<(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
    return !(left_hand_side >= right_hand_side);
  };
  friend constexpr bool operator<=(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
    return (left_hand_side.serial_date < right_hand_side.serial_date) ||
           ((left_hand_side.serial_date == right_hand_side.serial_date) &&
            (left_hand_side.time_ms <= right_hand_side.time_ms));
  };
  friend constexpr bool operator>(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
    return !(left_hand_side <= right_hand_side);
  };
};

}  // namespace chrono

/**
 * Display datetime
 */
inline std::ostream& operator<<(std::ostream& ostream, const chrono::datetime& datetime) {
  const auto [civil_year, civil_month, civil_day] = datetime.civil_date();
  const auto [hour, minute, second, millisecond] = datetime.time();
  ostream << civil_year << '-' << std::setfill('0') << std::setw(2) << civil_month << '-' << std::setfill('0')
          << std::setw(2) << civil_day << "T" << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0')
          << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << "." << std::setfill('0')
          << std::setw(3) << millisecond;
  return ostream;
}

#endif
