#ifndef INTERVAL
#define INTERVAL

#include "constants.h"

namespace raytracer
{
    class Interval
    {
    public:
        Interval() : min(-INFINITY), max(INFINITY) {}
        Interval(float min, float max) : min(min), max(max) {}
        bool Contains(float x, bool inclusive) const;
        float Clamp(float x) const;
        float Min() const {return min;}
        float Max() const {return max;}
        
        static const Interval Empty, Universe;

    private:
        float min;
        float max;
    };
} // namespace raytracer

#endif