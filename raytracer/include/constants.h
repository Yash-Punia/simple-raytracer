#ifndef CONSTANTS
#define CONSTANTS

#include <limits>
#include <memory>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "vec3.h"
#include "ray.h"
#include "interval.h"

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double PI = 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
    return degrees * PI / 180.0;
}

inline double random()
{
    // srand(time(0));
    return rand() / (RAND_MAX + 1.0);
}

inline double random(double min, double max)
{
    return min + (max - min) * random();
}

namespace raytracer
{
    const float ASPECT_RATIO = 16.0 / 9.0;
    const int W = 960;
    const int H = static_cast<int>(W / ASPECT_RATIO) < 1 ? 1 : static_cast<int>(W / ASPECT_RATIO);

    // Vec3 Utils

    static Vec3 Random()
    {
        return Vec3(random(), random(), random());
    }

    static Vec3 Random(double min, double max)
    {
        return Vec3(random(min, max), random(min, max), random(min, max));
    }

    static Vec3 Random(Vec3 min, Vec3 max)
    {
        return Vec3(random(min.x(), max.x()), random(min.y(), max.y()), random(min.z(), max.z()));
    }

    static Vec3 Reflect(const Vec3 &v, const Vec3 &n)
    {
        return v - 2*Dot(v,n)*n;
    }

    static Vec3 Refract(const Vec3 &v, const Vec3 &n, float ratio)
    {
        auto cosTheta = fmin(Dot(-v, n), 1.0);
        Vec3 rOutPerp =  ratio * (v + cosTheta*n);
        Vec3 rOutParallel = -sqrt(fabs(1.0 - Dot(rOutPerp, rOutPerp))) * n;
        return rOutPerp + rOutParallel;
    }

    inline Vec3 RandomInUnitSphere()
    {
        while (true)
        {
            Vec3 p = Random(-1, 1);
            if (Dot(p, p) < 1)
                return p;
        }
    }

    inline Vec3 RandomInUnitDisk()
    {
        while (true)
        {
            Vec3 p = Vec3(random(-1,1), random(-1,1), 0);
            if (Dot(p,p) < 1)
                return p;
        }
    }

    inline Vec3 RandomUnitVector()
    {
        return UnitVector(RandomInUnitSphere());
    }

    inline Vec3 RandomInHemisphere(Vec3 normal)
    {
        auto unitVector = RandomUnitVector();
        if (Dot(unitVector, normal) > 0)
            return unitVector;
        else
            return -unitVector;
    }

} // namespace raytracer

#endif