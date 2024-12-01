#include "chrono/year_fractions.h"
#include <algorithm>

namespace chrono {
double year_fraction_actual_actual(const Datetime start, const Datetime end) {
  Datetime true_start = std::min(start, end);
  Datetime true_end;
  double multiplier;
  if (true_start == start) {
    true_end = end;
    multiplier = 1.0;
  } else {
    true_end = start;
    multiplier = -1.0;
  }

  auto [start_year, start_month, start_day] = true_start.civil_date();
  auto [end_year, end_month, end_day] = true_end.civil_date();

  int years_difference = end_year - start_year;

  double first_year_diff;
  double last_year_diff{0.0};
  double last_year_days{365.0};
  double first_year_days{365.0 + is_leap(start_year)};
  double years_between{0.0};

  if (years_difference == 0) {
    first_year_diff = true_end - true_start;
  } else {
    first_year_diff = Datetime(start_year + 1, 1, 1) - true_start;
    last_year_diff = true_end - Datetime(end_year, 1, 1);
    last_year_days += is_leap(end_year);
    years_between = years_difference - 1;
  }

  return ((first_year_diff / first_year_days) + (last_year_diff / last_year_days) + years_between) * multiplier;
}
}  // namespace chrono
