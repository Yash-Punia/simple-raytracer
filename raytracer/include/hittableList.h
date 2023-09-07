#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "hittable.h"

using std::make_shared;
using std::shared_ptr;
using std::vector;

namespace raytracer
{
    class HittableList : public Hittable
    {
    public:
        HittableList() {}

        void Add(shared_ptr<Hittable> object);
        void Clear();
        bool Hit(const Ray& r, Interval interval, HitInfo &hitInfo) const override;

        vector<shared_ptr<Hittable>> Objects() const { return objects; }

    private:
        vector<shared_ptr<Hittable>> objects;
    };
} // namespace raytracer

#endif