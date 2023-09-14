#ifndef DIELECTRIC
#define DIELECTRIC

#include "Materials/material.h"
#include "hittable.h"

namespace raytracer
{
    class Dielectric : public Material
    {
    public:
        Dielectric(double refractiveIndex) : ir(refractiveIndex) {}
        bool Scatter(const Ray &ray, const HitInfo &hitInfo, Vec3 &attenuation, Ray &scattered) const;
    private:
        double ir;
        static double Reflectance(float cosine, float rIndex)
        {
            auto r0 = (1-rIndex) / (1+rIndex);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
    };
} // namespace raytracer


#endif