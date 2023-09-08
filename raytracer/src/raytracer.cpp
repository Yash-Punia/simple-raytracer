#include <iostream>
#include "raytracer.h"
#include "constants.h"
#include "sphere.h"
#include "Materials/material.h"

namespace raytracer
{
    Raytracer::Raytracer()
    {
        LightSource = Vec3(0, 0, 0);
        SamplesPerPixel = 500;
        MaxDepth = 10;
    }

    Vec3 Raytracer::RayColor(const Hittable &world, const Ray &ray, int depth)
    {
        if (depth <= 0)
            return Vec3(0,0,0);

        HitInfo hitInfo;
        if (world.Hit(ray, Interval(0.001, INFINITY), hitInfo))
        {
            Vec3 attenuation;
            Ray scatteredRay;
            if (hitInfo.mat->Scatter(ray, hitInfo, attenuation, scatteredRay));
                return attenuation * RayColor(world, Ray(hitInfo.point, scatteredRay.Direction()), depth-1);
            return Vec3(0,0,0);
        }

        Vec3 unitDirection = UnitVector(ray.Direction());
        float a = 0.5 * (ray.Direction().y() + 1.0);
        return (1 - a) * Vec3(1, 1, 1) + a * Vec3(0.5, 0.7, 1.0);
    }

    void Raytracer::Update(Input &input)
    {
        float x = LightSource.x();
        float y = LightSource.y();

        x += input.Right ? 0.1f : 0;
        x += input.Left ? -0.1f : 0;
        y += input.Up ? 0.1f : 0;
        y += input.Down ? -0.1f : 0;

        LightSource.Set(x, y, 0);
    }

    void Raytracer::Process(const Hittable &world, Vec3 **pixels)
    {
        Vec3 viewportU = Vec3(VW, 0, 0);
        Vec3 viewportV = Vec3(0, -VH, 0);

        Vec3 pixelDeltaU = viewportU / W;
        Vec3 pixelDeltaV = viewportV / H;

        auto viewport_upper_left = CAMERA_CENTER - Vec3(0, 0, FOCAL_LENGTH) - viewportU / 2 - viewportV / 2;
        auto p = viewport_upper_left + 0.5 * (pixelDeltaU + pixelDeltaV);

        for (int j = 0; j < H; j++)
        {
            for (int i = 0; i < W; i++)
            {
                auto newColor = Vec3(0,0,0);
                for (int sample = 0; sample < SamplesPerPixel; sample++)
                {
                    Ray r = GetRay(j, i, p, pixelDeltaU, pixelDeltaV);
                    newColor = newColor + RayColor(world, r, MaxDepth);
                }
                newColor = newColor / (float) SamplesPerPixel;
                newColor = Vec3(sqrt(newColor.x()), sqrt(newColor.y()), sqrt(newColor.z()));
                pixels[j][i] = newColor;
            }
        }
    }

    Ray Raytracer::GetRay(const int &row, const int &col, Vec3 p, Vec3 pixelDeltaU, Vec3 pixelDeltaV)
    {
        auto pixelCenter = p + (pixelDeltaU * col) + (pixelDeltaV * row);
        auto pixelSample = pixelCenter + PixelSampleSquare(pixelDeltaU, pixelDeltaV);

        auto origin = CAMERA_CENTER;
        auto direction = pixelSample - origin;

        return Ray(origin, direction);
    }

    Vec3 Raytracer::PixelSampleSquare(const Vec3 &pixelDeltaU, const Vec3 &pixelDeltaV) const
    {
        auto px = -0.5 + random();
        auto py = -0.5 + random();
        return (px * pixelDeltaU) + (py * pixelDeltaV);
    }

} // namespace raytracer
