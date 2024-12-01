#ifndef CHRONO_YEAR_FRACTIONS_H_
#define CHRONO_YEAR_FRACTIONS_H_

#include "chrono/datetime.h"

namespace chrono {
/**
 * Return year fraction with Act/Act convention
 */
double year_fraction_actual_actual(const Datetime start, const Datetime end);
}  // namespace chrono

#endif
