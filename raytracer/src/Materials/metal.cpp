#include "Materials/metal.h"

namespace raytracer
{
    bool Metal::Scatter(const Ray &ray, const HitInfo &hitInfo, Vec3 &attenuation, Ray &scattered) const
    {
        Vec3 reflected = Reflect(UnitVector(ray.Direction()), hitInfo.normal);
        scattered = Ray(hitInfo.point, reflected + fuzz * RandomUnitVector());
        attenuation = albedo;
        return (Dot(scattered.Direction(), hitInfo.normal) > 0);
    }
    
} // namespace raytracer
