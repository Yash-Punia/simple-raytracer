#include "vec3.h"
#include "ray.h"

namespace raytracer
{
    Vec3 Ray::At(const float t) const
    {
        return origin + direction * t;
    }
} // namespace raytracer