#include "sphere.h"
#include "constants.h"
#include "hittable.h"

namespace raytracer
{
    bool Sphere::Hit(const Ray &r, Interval interval, HitInfo &hitInfo) const
    {
        auto oc = r.Origin() - center;
        auto a = Dot(r.Direction(), r.Direction());
        auto half_b = Dot(r.Direction(), oc);
        auto c = Dot(oc, oc) - radius * radius;
        auto discriminant = half_b * half_b - a * c;
        auto sqrtd = sqrt(discriminant);
        if (discriminant < 0)
        {
            hitInfo.t = -1.0;
            return false;
        }
        else
        {
            auto t = (-half_b - sqrtd) / a;
            if (interval.Contains(t, true) == false)
            {
                t = (-half_b + sqrtd) / a;
                if (interval.Contains(t, true) == false)
                    return false;
            }

            bool frontFace;

            hitInfo.t = t;
            hitInfo.point = r.At(t);
            Vec3 outwardNormal = hitInfo.point - center;
            hitInfo.SetFaceNormal(r, outwardNormal);
            hitInfo.mat = mat;

            return true;
        }
    }
} // namespace raytracer