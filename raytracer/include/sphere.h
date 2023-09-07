#ifndef SPHERE
#define SPHERE

#include "hittable.h"

namespace raytracer
{
    class Sphere : public Hittable
    {
    public:
        Sphere(Vec3 center, float radius) : center(center), radius(radius), color(Vec3(1,0,0)) {}
        Sphere(Vec3 center, float radius, Vec3 color) : center(center), radius(radius), color(color) {}

        bool Hit(const Ray& r, Interval interval, HitInfo &hitInfo) const;


    private:
        Vec3 center;
        float radius;
        Vec3 color;
    };
} // namespace raytracer


#endif