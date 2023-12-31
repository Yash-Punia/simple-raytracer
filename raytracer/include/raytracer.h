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
        void ResetPixels(Vec3 **pixels);

        int samples;
        int samplesPerPixel;
        int maxDepth;
        int numScatteredRays;
        Vec3 lookFrom;
        Vec3 lookAt;
        Vec3 cameraCenter;
        Vec3 vUp;
        float vFov;
        Vec3 w;
        Vec3 u;
        Vec3 v;
        float theta;
        float height;

        float defocusAngle; // Variation angle of rays through each pixel
        float focusDistance;
        float defocusRadius;
        Vec3 defocusU;
        Vec3 defocusV;

        float vh;
        float vw;

        Vec3 **renderBuffer;
    };
} // namespace raytracer

#endif