#ifndef RAYTRACER
#define RAYTRACER

#include "hittableList.h"
#include "input.h"

namespace raytracer
{
    class Raytracer
    {
    public:
        Raytracer();
        void Update(Input &input);
        void Process(const Hittable &world, Vec3 **pixels);

    private:
        Vec3 RayColor(const Hittable &world, const Ray &, int depth);
        Vec3 PixelSampleSquare(const Vec3 &pixelDeltaU, const Vec3 &pixelDeltaV) const;
        Ray GetRay(const int &row, const int &col, Vec3 p, Vec3 pixelDeltaU, Vec3 pixelDeltaV);
        Vec3 DefocusDiskSample();
        void ProcessAntiAliasing(Vec3 **pixels);

        Vec3 LightSource;
        int SamplesPerPixel;
        int MaxDepth;
    };
} // namespace raytracer

#endif