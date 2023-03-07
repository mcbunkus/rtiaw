#ifndef _RTIAW_CAMERA_H
#define _RTIAW_CAMERA_H

#include "ray.h"
#include "vec3.h"
class Camera {
public:
  Camera() {

    const auto aspectRatio = 16.0 / 9.0;
    auto height = 2.0;
    auto width = aspectRatio * height;
    auto focalLength = 1.0;

    origin = Point3(0.0, 0.0, 0.0);
    horizontal = Vec3(width, 0, 0);
    vertical = Vec3(0, height, 0);
    lowerLeftCorner =
        origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);
  }

  Ray getRay(double u, double v) const {
    return Ray(origin,
               lowerLeftCorner + u * horizontal + v * vertical - origin);
  }

private:
  Point3 origin;
  Point3 lowerLeftCorner;
  Vec3 horizontal;
  Vec3 vertical;
};

#endif // _RTIAW_CAMERA_H
