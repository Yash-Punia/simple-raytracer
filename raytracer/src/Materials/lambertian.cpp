#include "Materials/lambertian.h"

namespace raytracer
{
    bool Lambertian::Scatter(const Ray &ray, const HitInfo &hitInfo, Vec3 &attenuation, Ray &scattered) const
    {
        Vec3 scatterDirection = hitInfo.normal + RandomUnitVector();
        if (scatterDirection.NearZero())
            scatterDirection = hitInfo.normal;
     
        attenuation = albedo;
        scattered = Ray(hitInfo.point, scatterDirection);
        return true;
    }
    
} // namespace raytracer
