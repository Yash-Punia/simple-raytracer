#ifndef METAL
#define METAL

#include "Materials/material.h"
#include "hittable.h"

namespace raytracer
{
    class Metal : public Material
    {
    public:
        Metal(const Vec3 &color, double f) : albedo(color), fuzz(f < 1 ? f : 1) {}
        bool Scatter(const Ray &ray, const HitInfo &hitInfo, Vec3 &attenuation, Ray &scattered) const;
    private:
        Vec3 albedo;
        double fuzz;
    };
} // namespace raytracer


#endif