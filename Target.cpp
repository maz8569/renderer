#include "Target.h"
#include <iostream>


TGABuffer::TGABuffer(unsigned int width, unsigned int height)
{
	SetSize(width, height);
}

void TGABuffer::Save(std::string name)
{
	name += ".tga";
	unsigned short header[9] = {
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0100, 0x0100, // width and height
		0x0820 };

	FILE* f;
	fopen_s(&f, name.c_str(), "wb+");
	if (NULL == f) return;

	header[6] = width;
	header[7] = height;

	fwrite(header, 2, 9, f);
	fwrite(colorBuffer, 4, width * height, f);

}

void TGABuffer::SetSize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	ClearBuffer();

	colorBuffer = new unsigned int[width * height];
	depthBuffer = new float[width * height];
}

void TGABuffer::ClearColor(unsigned int r, unsigned int g, unsigned int b)
{
	unsigned int color = GetColorFromRGB(r, g, b);
	for (unsigned int i = 0; i < width * height; i++)
	{
		colorBuffer[i] = color;
	}
}

void TGABuffer::ClearDepth()
{
	for (unsigned int i = 0; i < width * height; i++)
	{
		depthBuffer[i] = clearDepth;
	}
}

void TGABuffer::ClearBuffer()
{
	delete[] colorBuffer;
	delete[] depthBuffer;
}

unsigned int TGABuffer::GetColorFromRGB(unsigned int r, unsigned int g, unsigned int b)
{
	return ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
}

void TGABuffer::setPixel(int x, int y, unsigned int color)
{
	colorBuffer[y * width + x] = color;
}

unsigned int* TGABuffer::getColorBuffer()
{
	return colorBuffer;
}

unsigned int TGABuffer::getWidth()
{
	return width;
}

unsigned int TGABuffer::getHeight()
{
	return height;
}
