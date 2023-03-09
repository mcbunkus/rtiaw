#include <cmath>
#include <iostream>
#include <memory>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include "util.h"

Color RayColor(const Ray &r, const Hittable &world, int depth)
{
    HitRecord rec;

    if (depth <= 0) return Color(0, 0, 0);

    // 0.001 to ignore hits that are basically zero, cleans up shadow "acne"
    if (world.hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Color attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, world, depth - 1);
        return Color(0.0, 0.0, 0.0);
    }

    // from here it's just the environment (just a sky)
    Vec3 unitDir = glm::normalize(r.direction());
    double t     = 0.5 * (unitDir.y + 1.0);

    // this returns a gradient
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

HittableList random_scene()
{
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(
        std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            auto choose_mat = randomFloat();
            Point3 center(a + 0.9 * randomFloat(), 0.2,
                          b + 0.9 * randomFloat());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    auto albedo     = randomVec3() * randomVec3();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    auto albedo     = randomVec3(0.5, 1);
                    auto fuzz       = randomFloat(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(
                        std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

int main()
{
    // Image
    const double aspectRatio  = 3.0 / 2.0;
    const int imageWidth      = 1200;
    const int imageHeight     = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth        = 10;

    // world
    HittableList world = random_scene();

    Point3 lookfrom(13, 2, 3);
    Point3 lookat(0, 0, 0);
    Vec3 vup(0, 1, 0);
    auto distToFocus = 10.0;
    double aperture  = 0.1;

    Camera camera(lookfrom, lookat, vup, 20.0, aspectRatio, aperture,
                  distToFocus);

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            Color pixel(0, 0, 0);

            for (int s = 0; s < samplesPerPixel; ++s)
            {
                auto u = (i + randomFloat()) / (imageWidth - 1);
                auto v = (j + randomFloat()) / (imageHeight - 1);

                Ray r = camera.getRay(u, v);
                pixel += RayColor(r, world, maxDepth);
            }
            WriteColor(std::cout, pixel, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}
