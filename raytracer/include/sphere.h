#ifndef SPHERE
#define SPHERE

#include "hittable.h"

namespace raytracer
{
    class Sphere : public Hittable
    {
    public:
        Sphere(Vec3 center, double radius, shared_ptr<Material> mat) : center(center), radius(radius), mat(mat) {}

        bool Hit(const Ray& r, Interval interval, HitInfo &hitInfo) const;

    private:
        Vec3 center;
        double radius;
        shared_ptr<Material> mat;
        
    };
} // namespace raytracer


#endif