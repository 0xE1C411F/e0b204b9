#include "chrono/year_fractions.h"
#include "chrono/datetime.h"
#include "helpers/comparisons.h"
#include "helpers/test_session.h"

double DURATION_TOLERANCE = (double)0.001 / chrono::MILLISECONDS_IN_DAY / 365;

bool actual_actual() {
  double result{0.0};
  bool passed{true};

  result = chrono::year_fraction_actual_actual(chrono::Datetime{2020, 1, 1}, chrono::Datetime{2021, 1, 1});
  passed = passed & helpers::is_double_equal(result, 1.0, DURATION_TOLERANCE);

  result = chrono::year_fraction_actual_actual(chrono::Datetime{1000, 1, 1}, chrono::Datetime{4000, 1, 1});
  passed = passed & helpers::is_double_equal(result, 3000.0, DURATION_TOLERANCE);

  result = chrono::year_fraction_actual_actual(chrono::Datetime{4000, 1, 1}, chrono::Datetime{1000, 1, 1});
  passed = passed & helpers::is_double_equal(result, -3000.0, DURATION_TOLERANCE);

  result = chrono::year_fraction_actual_actual(chrono::Datetime{2020, 1, 1, 12, 30}, chrono::Datetime{2020, 6, 15});
  passed = passed & helpers::is_double_equal(result, 0.45212887067395263, DURATION_TOLERANCE);

  result = chrono::year_fraction_actual_actual(chrono::Datetime{2020, 6, 15}, chrono::Datetime{2020, 1, 1, 12, 30});
  passed = passed & helpers::is_double_equal(result, -0.45212887067395263, DURATION_TOLERANCE);

  result = chrono::year_fraction_actual_actual(chrono::Datetime{2020, 6, 15}, chrono::Datetime{2020, 1, 1});
  passed = passed & helpers::is_double_equal(result, -0.45355191256830601, DURATION_TOLERANCE);
  return passed;
}

int main() {
  return helpers::run_test_session({
      TEST_FUNCTION(actual_actual),
  });
}
