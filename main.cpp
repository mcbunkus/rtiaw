#include <cmath>
#include <iostream>
#include <memory>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "util.h"
#include "vec3.h"

Color RayColor(const Ray &r, const Hittable &world, int depth) {
  HitRecord rec;

  if (depth <= 0)
    return Color(0, 0, 0);
  if (world.hit(r, 0, infinity, rec)) {
    Point3 target = rec.p + rec.normal + randomInUnitSphere();
    return 0.5 * RayColor(Ray(rec.p, target - rec.p), world, depth - 1);
  }
  Vec3 unitDir = unitVector(r.direction());
  auto t = 0.5 * (unitDir.y() + 1.0);
  return (1.0 - t) * Color(1, 1, 1) + t * Color(0.5, 0.7, 1.0);
}

int main() {

  // Image
  const auto aspectRatio = 16.0 / 9.0;
  const int imageWidth = 1024;
  const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
  const int samplesPerPixel = 100;
  const int maxDepth = 50;

  // world
  HittableList world;
  world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  // Camera
  Camera camera;

  // le render

  std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int j = imageHeight - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < imageWidth; ++i) {
      Color pixel(0, 0, 0);

      for (int s = 0; s < samplesPerPixel; ++s) {

        auto u = (i + randomDouble()) / (imageWidth - 1);
        auto v = (j + randomDouble()) / (imageHeight - 1);

        Ray r = camera.getRay(u, v);
        pixel += RayColor(r, world, maxDepth);
      }
      WriteColor(std::cout, pixel, samplesPerPixel);
    }
  }

  std::cerr << "\nDone.\n";
}
