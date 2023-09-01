#include "raylib.h"
#include "iostream"

const int W = 256;
const int H = 256;

void DrawPixels()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			float r = float(i) / (W - 1);
			float g = float(j) / (H - 1);

			Vector4 colorNormalized = {r, g, 0.0f, 1.0f};
			Color c = ColorFromNormalized(colorNormalized);

			DrawPixel(i, j, c);
		}
	}
}

int main()
{
	InitWindow(W, H, "Simple Raytracer");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		DrawPixels();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
