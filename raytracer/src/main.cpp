#include <iostream>
#include "constants.h"
#include "raylib.h"
#include "raytracer.h"
#include "input.h"
#include "sphere.h"

using namespace raytracer;

Vec3 **pixels;

void Render();
void InitPixels();
void ClearPixels();

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
	world.Add(make_shared<Sphere>(Vec3(0, 0, -1), 0.5, Vec3(0.0, 0.0, 1.0)));
	world.Add(make_shared<Sphere>(Vec3(0, -100.5, -1), 100, Vec3(0, 1, 0)));
	world.Add(make_shared<Sphere>(Vec3(-2, -0.5, -2), 0.3));

	while (!WindowShouldClose())
	{
		// Update

		input.Right = IsKeyDown(KEY_RIGHT);
		input.Left = IsKeyDown(KEY_LEFT);
		input.Up = IsKeyDown(KEY_UP);
		input.Down = IsKeyDown(KEY_DOWN);

		rt.Update(input);

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