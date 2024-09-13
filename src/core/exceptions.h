#ifndef CORE_EXCEPTIONS_H_
#define CORE_EXCEPTIONS_H_

#include <stdexcept>

namespace core {
/**
 * Check condition and throw exception if not satisfied
 */
constexpr void require(bool condition, const char* error_message = "required condition not satisfied") {
  if (!condition) {
    throw std::invalid_argument(error_message);
  }
}
}  // namespace core

#endif
