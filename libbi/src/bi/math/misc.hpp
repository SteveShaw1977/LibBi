/**
 * @file
 *
 * Miscellaneous math functions.
 *
 * @author Lawrence Murray <lawrence.murray@csiro.au>
 * $Rev$
 * $Date$
 */
#ifndef BI_MATH_MISC_HPP
#define BI_MATH_MISC_HPP

#include "scalar.hpp"

namespace bi {
/**
 * Factorial.
 *
 * @group math
 */
CUDA_FUNC_BOTH int factorial(const int n);

/**
 * Least power of 2 greater than or equal to argument.
 *
 * @param n Argument.
 *
 * @return Least power of 2 greater than or equal to argument.
 */
CUDA_FUNC_BOTH int next_power_2(const int n);

/**
 * Relative error between two floating points.
 */
CUDA_FUNC_BOTH double rel_err(const double a, const double b);

/**
 *
 */
template<class T>
CUDA_FUNC_BOTH int is_finite(const T x);

}

inline int bi::factorial(const int n) {
  int result = 1u, y = n;

  while (y > 0) {
    result *= y;
    --y;
  }
  return result;
}

inline int bi::next_power_2(const int n) {
  int result = 1;
  while (result < n) {
    result <<= 1;
  }
  return result;
}

inline double bi::rel_err(const double a, const double b) {
  double diff = CUDA_ABS(a - b);
  double abs_a = CUDA_ABS(a);
  double abs_b = CUDA_ABS(b);

  if (a == b) { // absorbs a == b == 0.0 case
    return 0.0;
  } else {
    return (abs_a > abs_b) ? diff / abs_a : diff / abs_b;
  }
}

template<class T>
inline int bi::is_finite(const T x) {
  #ifdef USE_CPU
  return isfinite(x);
  #else
  return isfinite(x);
  #endif
}

#endif