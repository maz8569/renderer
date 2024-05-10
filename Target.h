#pragma once
#include <string>
#include "Vector3.h"

class TGABuffer
{

	unsigned int width;
	unsigned int height;
	float clearDepth = -100.f;


	unsigned int* colorBuffer;
	float* depthBuffer;

public:

	TGABuffer(unsigned int width, unsigned int height);

	void Save(std::string name);

	void SetSize(unsigned int width, unsigned int height);

	void ClearColor(unsigned int r, unsigned int g, unsigned int b);

	void ClearDepth();

	void ClearBuffer();

	static unsigned int GetColorFromRGB(unsigned int r, unsigned int g, unsigned int b);

	void setPixel(int x, int y, unsigned int color);

	unsigned int* getColorBuffer();

	unsigned int getWidth();
	unsigned int getHeight();

};

