#pragma once
#include "Vector3.h"

class Material
{
private:
	Vector3 Color_ = {0, 0, 0};

public:

	float specular_amount_ = 0.0f;
	float specular_coeff_ = 0.0f;
	bool reflect_fraction_ = false;
	float refract_fraction_ = 0.0f;

	Material();
	Material(Vector3 color);
	Material(Vector3 color, float specular_amount, float specular_coeff, bool reflect = false, float refract = 0.0f);
	Vector3 Color() const;
	void Color(Vector3 color);
};

