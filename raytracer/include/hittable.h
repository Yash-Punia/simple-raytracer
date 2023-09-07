#ifndef HITTABLE
#define HITTABLE

#include "constants.h"
#include "interval.h"

namespace raytracer
{
    struct HitInfo 
    {
        Vec3 point;
        Vec3 normal;
        bool frontFace;
        double t;

        void SetFaceNormal(const Ray &r, Vec3 outwardNormal)
        {
            if (Dot(r.Direction(), outwardNormal) > 0.0)
            {
                frontFace = false;
                outwardNormal = -outwardNormal;
            }
            else
                frontFace = true;
            
            normal = UnitVector(outwardNormal);
            frontFace = true;
        }
    };

    class Hittable
    {
    public:
        virtual ~Hittable() = default;
        virtual bool Hit(const Ray& r, Interval interval, HitInfo &hitInfo) const = 0;
    };
} // namespace raytracer


#endif