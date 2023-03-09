#ifndef _RTIAW_MATERIAL_H
#define _RTIAW_MATERIAL_H

#include <math.h>

#include <cmath>

#include "color.h"
#include "glm/ext/vector_double3.hpp"
#include "glm/geometric.hpp"
#include "glm/vec3.hpp"
#include "hittable.h"
#include "ray.h"
#include "util.h"

class Material
{
   public:
    virtual bool scatter(const Ray &rayIn, const HitRecord &rec,
                         Color &attenuation, Ray &scattered) const = 0;

    virtual ~Material() {}
};

class Lambertian : public Material
{
   public:
    Lambertian(const Color &color) : albedo(color) {}

    bool scatter(const Ray &rayIn, const HitRecord &rec, Color &attenuation,
                 Ray &scattered) const override
    {
        Vec3 scatterDir = rec.normal + randomUnitVector();

        // catch bad scatter dir
        if (vec3NearZero(scatterDir)) scatterDir = rec.normal;

        scattered   = Ray(rec.p, scatterDir);
        attenuation = albedo;
        return true;
    }

   public:
    Color albedo;
};

class Metal : public Material
{
   public:
    Metal(const Color &color, double fuzziness)
        : albedo(color), fuzziness(fuzziness < 1 ? fuzziness : 1)
    {
    }

    bool scatter(const Ray &rayIn, const HitRecord &rec, Color &attenuation,
                 Ray &scattered) const override
    {
        Vec3 reflected =
            glm::reflect(glm::normalize(rayIn.direction()), rec.normal);

        // fuzziness adds a little randomness to the reflections
        scattered   = Ray(rec.p, reflected + fuzziness * randomInUnitSphere());
        attenuation = albedo;
        return (glm::dot(scattered.direction(), rec.normal) > 0.0);
    }

   public:
    Color albedo;
    double fuzziness;
};

class Dielectric : public Material
{
   public:
    Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}
    bool scatter(const Ray &rayIn, const HitRecord &rec, Color &attenuation,
                 Ray &scattered) const override
    {
        attenuation         = Color(1.0, 1.0, 1.0);
        double refractRatio = rec.frontFace ? (1.0 / ir) : ir;
        Vec3 unitDir        = glm::normalize(rayIn.direction());

        double cosTheta = std::fmin(glm::dot(-unitDir, rec.normal), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = refractRatio * sinTheta > 1.0;
        Vec3 dir;

        if (cannotRefract ||
            reflectance(cosTheta, refractRatio) > randomFloat())
        {
            dir = glm::reflect(unitDir, rec.normal);
        }
        else
        {
            dir = glm::refract(unitDir, rec.normal, refractRatio);
        }

        scattered = Ray(rec.p, dir);
        return true;
    }

   private:
    // Use Schlick's approximation for reflectance
    static double reflectance(double cosine, double refIdx)
    {
        double r0 = (1 - refIdx) / (1 + refIdx);
        r0        = r0 * r0;

        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

   public:
    double ir;
};

#endif  // _RTIAW_MATERIAL_H
