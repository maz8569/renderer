#pragma once
#include "Primitive.h"

class Triangle : public Primitive
{
private:

public:

	Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Material material);

	virtual IntersectionResult Hit(const Ray& ray);
};

