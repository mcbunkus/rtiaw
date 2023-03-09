#ifndef _RTIAW_CAMERA_H
#define _RTIAW_CAMERA_H

#include <cmath>

#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/vector_double3.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"
#include "ray.h"
#include "util.h"

class Camera
{
   public:
    // vfov (vertical field of view in degrees)
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 vup, double vfov,
           double aspectRatio, double apeture, double focusDist)
    {
        double theta = deg2rad(vfov);
        double h     = std::tan(theta / 2);

        double height = 2.0 * h;
        double width  = aspectRatio * height;

        Vec3 w = glm::normalize(lookFrom - lookAt);
        Vec3 u = glm::normalize(glm::cross(vup, w));
        Vec3 v = glm::cross(w, u);

        origin     = lookFrom;
        horizontal = focusDist * width * u;
        vertical   = focusDist * height * v;
        lowerLeftCorner =
            origin - horizontal / 2.0 - vertical / 2.0 - focusDist * w;

        lensRadius = apeture / 2;
    }

    Ray getRay(double s, double t) const
    {
        Vec3 rd     = lensRadius * random_in_unit_disk();
        Vec3 offset = u * rd.x + v * rd.y;

        return Ray(origin + offset, lowerLeftCorner + s * horizontal +
                                        t * vertical - origin - offset);
    }

   private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lensRadius;
};

#endif  // _RTIAW_CAMERA_H
