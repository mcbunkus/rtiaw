#include "sphere.h"
#include "vec3.h"
#include <cmath>

bool Sphere::hit(const Ray &r, double tMin, double tMax, HitRecord &rec) const {
  Vec3 oc = r.origin() - center;
  auto a = r.direction().lengthSquared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.lengthSquared() - radius * radius;
  auto discriminant = half_b * half_b - a * c;

  if (discriminant < 0) {
    return false;
  }

  auto sqrtd = std::sqrt(discriminant);
  auto root = (-half_b - sqrtd) / a;
  if (root < tMin || tMax < root)
    return false;

  rec.t = root;
  rec.p = r.at(rec.t);
  Vec3 normal = (rec.p - center) / radius;
  rec.setFaceNormal(r, normal);

  return true;
}
