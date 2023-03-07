#ifndef _RTIAW_SPHERE_H
#define _RTIAW_SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class Sphere : public Hittable {
public:
  Sphere() = default;
  Sphere(Point3 cen, double r) : center(cen), radius(r) {}

  bool hit(const Ray &r, double tMin, double tMax,
           HitRecord &rec) const override;

private:
  Point3 center;
  double radius;
};

#endif // _RTIAW_SPHERE_H
