#ifndef MATERIAL
#define MATERIAL

#include "constants.h"

namespace raytracer
{
    class HitInfo;
    class Material
    {
    public:
        virtual bool Scatter(const Ray &ray, const HitInfo &hitInfo, Vec3 &attenuation, Ray &scattered) const = 0;
    };
} // namespace raytracer


#endif