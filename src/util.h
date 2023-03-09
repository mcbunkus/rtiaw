#ifndef _RTIAW_UTIL_H
#define _RTIAW_UTIL_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>

#include "glm/detail/qualifier.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/vec3.hpp"

using Vec3 = glm::vec<3, double>;

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi       = M_PI;

inline double deg2rad(double degrees) { return degrees * pi / 180.0; }

inline double randomFloat() { return rand() / (RAND_MAX + 1.0); }

inline double randomFloat(double min, double max)
{
    return min + (max - min) * randomFloat();
}

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline Vec3 randomVec3()
{
    return Vec3{randomFloat(), randomFloat(), randomFloat()};
}

inline Vec3 randomVec3(double min, double max)
{
    return Vec3{randomFloat(min, max), randomFloat(min, max),
                randomFloat(min, max)};
}

inline Vec3 randomInUnitSphere()
{
    while (true)
    {
        Vec3 random = randomVec3(-1, 1);
        if (glm::length2(random) >= 1) continue;
        return random;
    }
}

inline Vec3 randomUnitVector() { return glm::normalize(randomInUnitSphere()); }

inline Vec3 randomInHemisphere(const Vec3 &normal)
{
    Vec3 inUnitSphere = randomInUnitSphere();
    if (glm::dot(inUnitSphere, normal) > 0.0f)
    {
        return inUnitSphere;
    }
    else
    {
        return -inUnitSphere;
    }
}

inline bool vec3NearZero(const Vec3 &vec)
{
    const double s = 1e-8;
    return (glm::length2(vec) < s * s);
}

inline Vec3 random_in_unit_disk()
{
    while (true)
    {
        auto p = Vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
        if (glm::length2(p) >= 1) continue;
        return p;
    }
}

#endif  // _RTIAW_UTIL_H
