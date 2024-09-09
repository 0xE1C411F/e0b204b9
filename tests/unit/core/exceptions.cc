#include <stdexcept>
#include "core/exceptions.h"
#include "helpers/test_session_fakefile.h"

bool test_invalid_require() {
  try {
    core::require(0 > 1);
  } catch (std::invalid_argument const& ex) {
    return true;
  }
  return false;
}

bool test_valid_require() {
  try {
    core::require(1 > 0);
  } catch (std::invalid_argument const& ex) {
    return false;
  }
  return true;
}

int main() {
  return helpers::run_test_session({
      test_invalid_require,
      test_valid_require,
  });
}
