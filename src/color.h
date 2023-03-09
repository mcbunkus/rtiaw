#ifndef _RTIAW_COLOR_H
#define _RTIAW_COLOR_H

#include <cmath>
#include <ostream>

#include "glm/vec3.hpp"
#include "util.h"

using Color = Vec3;

inline void WriteColor(std::ostream &out, Color pixel, int samplesPerPixel)
{
    auto r = pixel.x;
    auto g = pixel.y;
    auto b = pixel.z;

    float scale = 1.0 / samplesPerPixel;
    // taking the sqrt of the scale * val here is gamma correction
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif  // _RTIAW_COLOR_H
