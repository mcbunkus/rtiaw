#ifndef _RTIAW_RAY_H
#define _RTIAW_RAY_H

#include "vec3.h"

using Point3 = Vec3;

class Ray {
private:
  Point3 m_origin;
  Vec3 m_dir;

public:
  Ray() = default;
  Ray(const Point3 &origin, const Vec3 &direction);

  Point3 origin() const;
  Vec3 direction() const;

  Point3 at(double t) const;

  ~Ray() {}
};

#endif // _RTIAW_RAY_H
