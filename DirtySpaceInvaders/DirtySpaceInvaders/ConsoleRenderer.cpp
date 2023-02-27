#include <vector>
#include <iostream>
#include "Vector.h"
#include "ConsoleRenderer.h"

#include <Windows.h>

void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

Renderer::Renderer(const Vector2D& bounds)
	: renderBounds(bounds)
{
	canvasSize = (int)(bounds.x * bounds.y);
	disp[0].canvas = new unsigned char[canvasSize];
	disp[1].canvas = new unsigned char[canvasSize];
}


Renderer::~Renderer()
{
	delete[] disp[0].canvas;
	delete[] disp[1].canvas;
}

void Renderer::Update(const RenderItemList& RenderList)
{
	FillCanvas(RS_BackgroundTile);

	for (auto ri : RenderList)
	{
		int x = int(ri.pos.x);
		int y = int(ri.pos.y);

		if (x >= 0 && x < renderBounds.x && y >= 0 && y < renderBounds.y)
		{
			*CurCanvas((int)ri.pos.x, +(int)ri.pos.y) = ri.sprite;
		}
	}

	DrawCanvas();
}

void Renderer::FillCanvas(unsigned char sprite)
{
	for (int i = 0; i < canvasSize; i++)
	{
		*CurCanvas(i, 0) = sprite;
	}
}

void Renderer::DrawCanvas()
{
	for (int y = 0; y < renderBounds.y; y++)
	{
		for (int x = 0; x < renderBounds.x; x++)
		{
			setCursorPosition(x, y);
			std::cout << *CurCanvas(x, y);
		}
		std::cout << std::endl;
	}

	curIdx++;
}

