#include "hittableList.h"

namespace raytracer
{
    void HittableList::Add(shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    void HittableList::Clear()
    {
        objects.clear();
    }

    bool HittableList::Hit(const Ray& r, Interval interval, HitInfo &hitInfo) const
    {
        HitInfo tempHit;
        bool hitAnything = false;
        auto closestSoFar = interval.Max();

        for (int i=0; i<objects.size(); i++)
        {
            if (objects[i]->Hit(r, Interval(interval.Min(), closestSoFar), tempHit))
            {
                hitAnything = true;
                closestSoFar = tempHit.t;
                hitInfo = tempHit;
            }
        }

        return hitAnything;
    }

} // namespace raytracer
