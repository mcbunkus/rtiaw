#ifndef _RTIAW_VEC3
#define _RTIAW_VEC3

#include <cmath>
#include <cstdint>
#include <iostream>

class Vec3 {

public:
  double e[3];

  Vec3();
  Vec3(double x, double y, double z);

  double x() const;
  double y() const;
  double z() const;

  Vec3 operator-() const;
  double operator[](int i) const;
  double &operator[](int i);

  Vec3 &operator+=(const Vec3 &v);

  Vec3 &operator*=(const double t);

  Vec3 operator/=(const double t);

  double length() const;
  double lengthSquared() const;

  static Vec3 random();
  static Vec3 random(double min, double max);

  ~Vec3();
};

// vec3 Utility Functions

inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
  return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) { return t * v; }

inline Vec3 operator/(Vec3 v, double t) { return (1 / t) * v; }

inline double dot(const Vec3 &u, const Vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unitVector(Vec3 v) { return v / v.length(); }

inline Vec3 randomInUnitSphere() {
  while (true) {
    auto p = Vec3::random(-1, 1);
    if (p.lengthSquared() >= 1)
      continue;
    return p;
  }
}

#endif // _RdoubleIAW_VEC3
