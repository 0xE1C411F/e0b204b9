#include <functional>
#include <vector>

namespace helpers {
int run_test(std::function<bool(void)> testing_function);
int run_test_session(std::vector<std::function<bool(void)>> unit_tests);
}  // namespace helpers
