#ifndef _RTIAW_SPHERE_H
#define _RTIAW_SPHERE_H

#include <memory>

#include "glm/vec3.hpp"
#include "hittable.h"
#include "material.h"
#include "ray.h"

class Sphere : public Hittable
{
   public:
    Sphere() = default;
    Sphere(Point3 cen, double r, std::shared_ptr<Material> material)
        : center(cen), radius(r), material(material)
    {
    }

    bool hit(const Ray &r, double tMin, double tMax,
             HitRecord &rec) const override;

   private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> material;
};

#endif  // _RTIAW_SPHERE_H
