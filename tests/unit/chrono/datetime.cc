#include "chrono/datetime.h"
#include "helpers/test_session.h"

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

int main() {
  return helpers::run_test_session({
      TEST_FUNCTION(datetime_invalid_day),
      TEST_FUNCTION(datetime_valid_initialisation),
  });
}
