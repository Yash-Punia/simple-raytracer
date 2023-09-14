#include "Materials/dielectric.h"

namespace raytracer
{
    bool Dielectric::Scatter(const Ray &ray, const HitInfo &hitInfo, Vec3 &attenuation, Ray &scattered) const
    {
        attenuation = Vec3(1.0, 1.0, 1.0);
        double ratio = hitInfo.frontFace ? (1.0 / ir) : ir;
        Vec3 unitDirection = UnitVector(ray.Direction());

        float cosTheta = fmin(Dot(-unitDirection, hitInfo.normal), 1.0);
        float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        Vec3 direction;
        if (ratio * sinTheta > 1.0 || Reflectance(cosTheta, ratio) > 0.6)
            direction = Reflect(unitDirection, hitInfo.normal);
        else
            direction = Refract(unitDirection, hitInfo.normal, ratio);
        scattered = Ray(hitInfo.point, direction);
        return true;
    }

} // namespace raytracer
