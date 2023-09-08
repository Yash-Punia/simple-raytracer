#ifndef RAY
#define RAY

namespace raytracer
{
    class Ray
    {
    public:
        Ray() {}
        Ray(Vec3 origin, Vec3 direction):origin(origin), direction(direction) {}
        Vec3 At(const float t) const;
        Vec3 Origin() const {return origin;}
        Vec3 Direction() const {return direction;}

    private:
        Vec3 origin;
        Vec3 direction;
    };
    
} // namespace raytracer


#endif