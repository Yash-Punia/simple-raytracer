#include "interval.h"

namespace raytracer
{
    bool Interval::Contains(float x, bool inclusive) const
    {
        return inclusive ? x <= max && min <= x : x < max && min < x;
    }

    float Interval::Clamp(float x) const
    {
        if (x > max) return max;
        if (x < min) return min;
        return x;
    }

    const Interval Interval::Empty(INFINITY, -INFINITY);
    const Interval Interval::Universe(-INFINITY, INFINITY);
} // namespace raytracer
