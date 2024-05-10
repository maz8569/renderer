#pragma once
#include <vector>
#include "Vector3.h"
#include "Triangle.h"
#include "Sphere.h"

class Model
{
private:
	std::vector<Vector3> vertices;
	std::vector<Vector3> texture;
	std::vector<Vector3> normals;
	std::vector<Triangle> triangles;

public:

	Sphere bounds;

	Model();
	Model(const char* filename);

	IntersectionResult render(Ray ray);

	bool loadOBJModel(const char* filename);

};

