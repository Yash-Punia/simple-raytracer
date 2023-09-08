#ifndef LAMBERTIAN
#define LAMBERTIAN

#include "Materials/material.h"
#include "hittable.h"

namespace raytracer
{
    class Lambertian : public Material
    {
    public:
        Lambertian(Vec3 color) : albedo(color) {}
        bool Scatter(const Ray &ray, const HitInfo &hitInfo, Vec3 &attenuation, Ray &scattered) const;
    private:
        Vec3 albedo;
    };
} // namespace raytracer


#endif