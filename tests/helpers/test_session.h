#ifndef _TEST_HELPERS_SESSION_H_
#define _TEST_HELPERS_SESSION_H_

#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#define TEST_FUNCTION(f) std::make_tuple(f, #f)

namespace helpers {
inline int run_test_session(std::vector<std::tuple<std::function<bool(void)>, const char*>> unit_tests) {
  std::cout << "\033[94m━┯━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m"
            << std::endl;
  int error_counter = 0;
  int number_of_tests = unit_tests.size();
  for (int test_number = 0; test_number < number_of_tests; test_number++) {
    const auto& [function, name] = unit_tests[test_number];
    std::cout << " \033[94m" << (test_number < (number_of_tests - 1) ? "├" : "└") << "\033[0m " << name
              << std::string(70 - strlen(name), ' ') << std::flush;
    if (!function()) {
      std::cout << "\033[31;1mFAILED\033[0m";
      error_counter++;
    } else {
      std::cout << "\033[32;1m✓\033[0m";
    }
    std::cout << std::endl;
  }
  return error_counter;
}
}  // namespace helpers

#endif
