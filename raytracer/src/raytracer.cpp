#include <iostream>
#include "raytracer.h"
#include "constants.h"
#include "sphere.h"
#include "Materials/material.h"

namespace raytracer
{
    Raytracer::Raytracer()
    {
        lookFrom = Vec3(0, 1, 1);
        lookAt = Vec3(0, 0, -1);
        cameraCenter = lookFrom;

        vUp = Vec3(0, 1, 0);
        vFov = 60;
        w = UnitVector(lookFrom - lookAt);
        u = UnitVector(Cross(vUp, w));
        v = Cross(w, u);

        theta = degrees_to_radians(vFov);
        height = tan(theta / 2);

        defocusAngle = 0;
        focusDistance = 2;

        defocusRadius = focusDistance * tan(degrees_to_radians(defocusAngle) / 2);

        defocusU = u * defocusRadius;
        defocusV = v * defocusRadius;

        vh = 2 * height * focusDistance;
        vw = vh * (static_cast<float>(W) / H);

        renderBuffer = new Vec3 *[H];

        for (int i = 0; i < H; i++)
            renderBuffer[i] = new Vec3[W];

        samples = 0;
        samplesPerPixel = 1;
        maxDepth = 6;
        numScatteredRays = 4;
    }

    Vec3 Raytracer::RayColor(const Hittable &world, const Ray &ray, int depth)
    {
        if (depth <= 0)
            return Vec3(0, 0, 0);

        HitInfo hitInfo;
        if (world.Hit(ray, Interval(0.001, INFINITY), hitInfo))
        {
            Vec3 attenuation;
            Ray scatteredRay;
            Vec3 color = Vec3(0, 0, 0);
            if (hitInfo.mat->Scatter(ray, hitInfo, attenuation, scatteredRay))
                return attenuation * RayColor(world, Ray(hitInfo.point, scatteredRay.Direction()), depth - 1);
            return Vec3(0, 0, 0);
        }

        Vec3 unitDirection = UnitVector(ray.Direction());
        float a = 0.5 * (unitDirection.y() + 1.0);
        return (1 - a) * Vec3(1, 1, 1) + a * Vec3(0.5, 0.7, 1.0);
    }

    void Raytracer::Update(Input &input)
    {
        float x = cameraCenter.x();
        float z = cameraCenter.z();

        x += input.Right ? 0.1f : 0;
        x += input.Left ? -0.1f : 0;
        z += input.Up ? -0.1f : 0;
        z += input.Down ? 0.1f : 0;

        cameraCenter.Set(x, cameraCenter.y(), z);

        if (input.Right || input.Left || input.Up || input.Down)
            samples = 0;
    }

    void Raytracer::Process(const Hittable &world, Vec3 **pixels)
    {
        Vec3 viewportU = vw * u;
        Vec3 viewportV = vh * -v;

        Vec3 pixelDeltaU = viewportU / W;
        Vec3 pixelDeltaV = viewportV / H;

        auto viewport_upper_left = cameraCenter - (focusDistance * w) - viewportU / 2 - viewportV / 2;
        auto p = viewport_upper_left + 0.5 * (pixelDeltaU + pixelDeltaV);

        if (samples == 0)
        {
            ResetPixels(pixels);
            ResetPixels(renderBuffer);
        }

        if (samples == 100)
            return;

        samples++;
        std::cout << "Samples: " << samples << "\n";

        for (int j = 0; j < H; j++)
        {
            for (int i = 0; i < W; i++)
            {
                Ray r = GetRay(j, i, p, pixelDeltaU, pixelDeltaV);
                Vec3 color = RayColor(world, r, maxDepth);
                renderBuffer[j][i] = renderBuffer[j][i] + color;
                pixels[j][i] = renderBuffer[j][i] / samples;
            }
        }
    }

    Ray Raytracer::GetRay(const int &row, const int &col, Vec3 p, Vec3 pixelDeltaU, Vec3 pixelDeltaV)
    {
        auto pixelCenter = p + (pixelDeltaU * col) + (pixelDeltaV * row);
        auto pixelSample = pixelCenter + PixelSampleSquare(pixelDeltaU, pixelDeltaV);

        auto origin = (defocusAngle <= 0) ? cameraCenter : DefocusDiskSample();
        auto direction = pixelSample - origin;

        return Ray(origin, direction);
    }

    Vec3 Raytracer::PixelSampleSquare(const Vec3 &pixelDeltaU, const Vec3 &pixelDeltaV) const
    {
        auto px = -0.5 + random();
        auto py = -0.5 + random();
        return (px * pixelDeltaU) + (py * pixelDeltaV);
    }

    Vec3 Raytracer::DefocusDiskSample()
    {
        auto p = RandomInUnitDisk();
        return cameraCenter + (p.x() * u) + (p.y() * v);
    }

    void Raytracer::ResetPixels(Vec3 **pixels)
    {
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                pixels[i][j] = Vec3(0, 0, 0);
    }

} // namespace raytracer
