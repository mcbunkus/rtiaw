#ifndef _RTIAW_COLOR_H
#define _RTIAW_COLOR_H

#include "util.h"
#include "vec3.h"
#include <ostream>

using Color = Vec3;

inline void WriteColor(std::ostream &out, Color pixel, int samplesPerPixel) {
  auto r = pixel.x();
  auto g = pixel.y();
  auto b = pixel.z();

  auto scale = 1.0 / samplesPerPixel;
  r *= scale;
  g *= scale;
  b *= scale;

  out << static_cast<int>(255.999 * clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(255.999 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif // _RTIAW_COLOR_H
