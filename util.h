#ifndef _RTIAW_UTIL_H
#define _RTIAW_UTIL_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = M_2_PI;

inline double deg2rad(double degrees) { return degrees * pi / 180.0; }

inline double randomDouble() { return rand() / (RAND_MAX + 1.0); }

inline double randomDouble(double min, double max) {
  return min + (max - min) * randomDouble();
}

inline double clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

#endif // _RTIAW_UTIL_H
