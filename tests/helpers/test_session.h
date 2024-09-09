#ifndef _TEST_HELPERS_SESSION_H_
#define _TEST_HELPERS_SESSION_H_

#include <functional>
#include <iostream>
#include <vector>

namespace helpers {
inline int run_test(std::function<bool(void)> testing_function) {
  bool outcome = testing_function();
  if (outcome) {
    std::cout << '.' << std::flush;
  } else {
    std::cout << 'E' << std::flush;
  }
  return (int)!outcome;
}

inline int run_test_session(std::vector<std::function<bool(void)>> unit_tests) {
  int error_counter = 0;
  for (auto unit_test : unit_tests) {
    error_counter += run_test(unit_test);
  }
  std::cout << ' ' << std::flush;
  return error_counter;
}
}  // namespace helpers

#endif
