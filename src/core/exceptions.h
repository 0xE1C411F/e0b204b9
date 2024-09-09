#ifndef CORE_EXCEPTIONS_H_
#define CORE_EXCEPTIONS_H_

#include <stdexcept>
#include <string>

namespace core {
/**
 * Check condition and throw exception if not satisfied
 */
inline void require(bool condition, const std::string& error_message = "required condition not satisfied") {
  if (!condition) {
    throw std::invalid_argument(error_message);
  }
}
}  // namespace core

#endif
