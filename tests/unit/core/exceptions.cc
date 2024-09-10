#include "core/exceptions.h"
#include <stdexcept>
#include "helpers/test_session.h"

bool throwing_require() {
  try {
    core::require(0 > 1);
  } catch (std::invalid_argument const& ex) {
    return true;
  }
  return false;
}

bool satisfied_require() {
  try {
    core::require(1 > 0);
  } catch (std::invalid_argument const& ex) {
    return false;
  }
  return true;
}

int main() {
  return helpers::run_test_session({
      TEST_FUNCTION(throwing_require),
      TEST_FUNCTION(satisfied_require),
  });
}
