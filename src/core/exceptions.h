#ifndef CORE_EXCEPTIONS_H_
#define CORE_EXCEPTIONS_H_

#include <stdexcept>

namespace core {
/**
 * Check condition and throw exception if not satisfied
 */
inline void require(bool condition) {
  if (!condition) {
    throw std::invalid_argument("required condition not satisfied");
  }
}
}  // namespace core

#endif
