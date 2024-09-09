#include "chrono/datetime.h"
#include "core/exceptions.h"

namespace chrono {

/*====================================================================================================================*
 * datetime class
 *====================================================================================================================*/
/* constructor
 * -------------------------------------------------------------------------------------------------------------------*/
datetime::datetime(int year, int month, int day, int hour, int minute, int second, int millisecond) {
  core::require((year >= 0) && (year <= 100'000), "year is not in valid range [0, 100'000]");
  core::require((month >= 1) && (month <= 12), "month is not in valid range [1, 12]");
  const int max_day = last_day_of_month(month, year);
  core::require((day >= 1) && (day <= max_day), "day is not in valid range [1, " + std::to_string(max_day) + "]");
  core::require((hour >= 0) & (hour < 24), "hour is not in valid range [0, 24)");
  core::require((minute >= 0) && (minute < 60), "minute is not in valid range [0, 60)");
  core::require((second >= 0) && (second < 60), "second is not in valid range [0, 60)");
  core::require((millisecond >= 0) && (millisecond < 1'000), "millisecond is not in valid range [0, 1'000)");

  /* date conversion (days_from_civil) */
  year -= month <= 2;                  /* the year starts on march 1st, allowing the leap day to be the last */
  const int standard_era = year / 400; /* the gregorian calendar has eras of 400 years */
  const int year_of_standard_era = year - standard_era * 400;

  /* month is converted in a standard month, the 153 x + 2 / 5 takes advantage of rounding to get the correct number of
   * days for each month (note that this is possible because of having placed february 29th as the last day of the year
   */
  const int day_of_year = (153 * (month > 2 ? month - 3 : month + 9) + 2) / 5 + day - 1;

  const int day_of_standard_era =
      year_of_standard_era * 365 + year_of_standard_era / 4 - year_of_standard_era / 100 + day_of_year;

  serial_date = standard_era * DAYS_IN_ERA + day_of_standard_era;
  time_ms = hour * 3'600'000 + minute * 60'000 + second * 1'000 + millisecond;
}

/* internal-to-civil API
 * -------------------------------------------------------------------------------------------------------------------*/
constexpr std::tuple<int, int, int> datetime::civil_date() const noexcept {
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
/*====================================================================================================================*/

/* utility function
 * -------------------------------------------------------------------------------------------------------------------*/
constexpr bool is_leap(int year) noexcept {
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

/* utility function
 * -------------------------------------------------------------------------------------------------------------------*/
constexpr int last_day_of_month(int month, int year) noexcept {
  constexpr unsigned char days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return month != 2 || !is_leap(year) ? days[month - 1] : 29;
}

/* utility function
 * -------------------------------------------------------------------------------------------------------------------*/
constexpr double operator-(const datetime& left_hand_side, const datetime& right_hand_side) noexcept {
  return (double)(left_hand_side.serial_date - right_hand_side.serial_date) +
         ((double)(left_hand_side.time_ms - right_hand_side.time_ms)) / (double)MILLISECONDS_IN_DAY;
};
}  // namespace chrono

/* utility function
 * -------------------------------------------------------------------------------------------------------------------*/
constexpr std::ostream& operator<<(std::ostream& ostream, const chrono::datetime& datetime) {
  const auto [civil_year, civil_month, civil_day] = datetime.civil_date();
  ostream << civil_year << '-' << civil_month << '-' << civil_day;
  return ostream;
}
