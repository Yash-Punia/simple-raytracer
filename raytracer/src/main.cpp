#include <iostream>
#include "constants.h"
#include "raylib.h"
#include "raytracer.h"
#include "input.h"
#include "sphere.h"
#include "Materials/lambertian.h"
#include "Materials/metal.h"
#include "Materials/dielectric.h"

using namespace raytracer;

Vec3 **pixels;

void Render();
void InitPixels();
Vec3 GetRandomPosition();
shared_ptr<raytracer::Material> GetRandomMaterial();

int main()
{
	InitWindow(W, H, "Simple Raytracer");

	Raytracer rt;
	Input input;
	InitPixels();

	std::cout << W << std::endl;
	std::cout << H << std::endl;
	std::cout << VW << std::endl;
	std::cout << VH << std::endl;

	HittableList world;
	// world.Add(make_shared<Sphere>(Vec3(0, 0, -1), 0.5, Vec3(0.0, 0.0, 1.0)));
	// world.Add(make_shared<Sphere>(Vec3(0, -100.5, -1), 100, Vec3(0, 1, 0)));
	// world.Add(make_shared<Sphere>(Vec3(-2, -0.5, -2), 0.3));

	// DIELECTRIC TESTING
	
    // shared_ptr<raytracer::Material> GroundMat = make_shared<Lambertian>(Vec3(0.6, 0.8, 0.0));
    // shared_ptr<raytracer::Material> CenterMat = make_shared<Lambertian>(Vec3(0.1, 0.2, 0.5));
    // shared_ptr<raytracer::Material> LeftMat   = make_shared<Dielectric>(10);
    // shared_ptr<raytracer::Material> RightMat  = make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 0.0);

    // world.Add(make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, GroundMat));
    // world.Add(make_shared<Sphere>(Vec3( 0.0,    0.0, -1.0),   0.5, CenterMat));
    // world.Add(make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),   0.5, LeftMat));
    // world.Add(make_shared<Sphere>(Vec3( 1.0,    0.0, -1.0),   0.5, RightMat));

	// FOV TESTING
	// auto R = cos(PI/4);

    // auto material_left  = make_shared<Lambertian>(Vec3(0,0,1));
    // auto material_right = make_shared<Lambertian>(Vec3(1,0,0));

    // world.Add(make_shared<Sphere>(Vec3(-R, 0, -1), R, material_left));
    // world.Add(make_shared<Sphere>(Vec3( R, 0, -1), R, material_right));

	// CAM POSITIONING
	auto material_ground = make_shared<Lambertian>(Vec3(0.8, 0.8, 0.0));
    // auto material_center = make_shared<Lambertian>(Vec3(1, 0.2, 0.5));
    // auto material_left   = make_shared<Dielectric>(5);
    // auto material_right  = make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 0.0);

    // world.Add(make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.Add(make_shared<Sphere>(Vec3( 0.0,    0.0, -1.0),   0.5, material_center));
    // world.Add(make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.Add(make_shared<Sphere>(Vec3(-1.0,    0.0, -1.0),  0.4, material_left));
    // world.Add(make_shared<Sphere>(Vec3( 1.0,    0.0, -1.0),   0.5, material_right));

	// RANDOMIZED!!
	auto totalBalls = 10;

	world.Add(make_shared<Sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, material_ground));

	for (int i=0; i<totalBalls; i++)
	{
		world.Add(make_shared<Sphere>(GetRandomPosition(), 0.5, GetRandomMaterial()));
	}

	while (!WindowShouldClose())
	{
		// Update

		input.Right = IsKeyDown(KEY_RIGHT);
		input.Left = IsKeyDown(KEY_LEFT);
		input.Up = IsKeyDown(KEY_UP);
		input.Down = IsKeyDown(KEY_DOWN);

		// rt.Update(input);

		// Render
		BeginDrawing();
		ClearBackground(WHITE);

		rt.Process(world, pixels);

		Render();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void InitPixels()
{
	pixels = new Vec3 *[H];

	for (int i = 0; i < H; i++)
		pixels[i] = new Vec3[W];
}

void Render()
{
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			Vec3 pixel = pixels[i][j];

			float r = pixel.x();
			float g = pixel.y();
			float b = pixel.z();

			Color c;
			c.r = static_cast<unsigned char>(r * 255.99);
			c.g = static_cast<unsigned char>(g * 255.99);
			c.b = static_cast<unsigned char>(b * 255.99);
			c.a = 255;

			DrawPixel(j, i, c);
		}
	}
}

shared_ptr<raytracer::Material> GetRandomMaterial()
{
	auto randValue = random();

	// Lambertian
	if (randValue < 0.3)
		return make_shared<Lambertian>(Vec3(random(), random(), random()));

	if (randValue < 0.6)
		return make_shared<Metal>(Vec3(random(), random(), random()), 0.3);

	return make_shared<Dielectric>(random(2, 5));
}

Vec3 GetRandomPosition()
{
	return Vec3(random(-3,2), 0, random(-3,2));
}