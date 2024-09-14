#ifndef _TEST_HELPERS_COMPARISONS_H_
#define _TEST_HELPERS_COMPARISONS_H_

namespace helpers {
constexpr bool is_double_equal(const double left, const double right, const double tolerance = 0.0) {
  return ((left - right) < tolerance) && ((left - right) > -tolerance);
}
}  // namespace helpers

#endif
