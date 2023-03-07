#ifndef _RTIAW_HITTABLE_H
#define _RTIAW_HITTABLE_H

#include "ray.h"
#include "vec3.h"
struct HitRecord {
  Point3 p;
  Vec3 normal;
  double t;
  bool frontFace;

  inline void setFaceNormal(const Ray &r, const Vec3 &outwardNormal) {
    frontFace = dot(r.direction(), outwardNormal);
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

class Hittable {
public:
  virtual bool hit(const Ray &r, double tMin, double tMax,
                   HitRecord &rec) const = 0;
  virtual ~Hittable() = default;
};

#endif // _RTIAW_HITTABLE_H
