#include "vec3.h"
#include "util.h"

Vec3::Vec3() : e{0, 0, 0} {}
Vec3::Vec3(double x, double y, double z) : e{x, y, z} {}

double Vec3::x() const { return e[0]; }
double Vec3::y() const { return e[1]; }
double Vec3::z() const { return e[2]; }

Vec3 Vec3::operator-() const { return Vec3{-e[0], -e[1], -e[2]}; }
double Vec3::operator[](int i) const { return e[i]; }
double &Vec3::operator[](int i) { return e[i]; }

Vec3 &Vec3::operator+=(const Vec3 &v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

Vec3 &Vec3::operator*=(const double t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

Vec3 Vec3::operator/=(const double t) { return *this *= 1 / t; }

double Vec3::length() const { return std::sqrt(lengthSquared()); }
double Vec3::lengthSquared() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

Vec3 Vec3::random() {
  return Vec3{randomDouble(), randomDouble(), randomDouble()};
}

Vec3 Vec3::random(double min, double max) {
  return Vec3{randomDouble(min, max), randomDouble(min, max),
              randomDouble(min, max)};
}

Vec3::~Vec3() {}
