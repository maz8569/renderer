#pragma once
#include "Bound.h"

class Plane : public Bound
{
public:
	
	Vector3 punkt;
	Vector3 normal;

	Plane();
	Plane(Vector3 normal, Vector3 punkt);
	Plane(Vector3 normal, Vector3 punkt, Material material);

	float AnglePlane(Plane plane);

	virtual IntersectionResult Hit(const Ray& ray);

};

std::ostream& operator<<(std::ostream& strm, const Plane& plane);