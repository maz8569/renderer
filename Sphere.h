#pragma once
#include <vector>
#include "Bound.h"


class Sphere : public Bound
{
	Vector3 Center_;
	float Radius_;

public:

	Sphere();
	Sphere(const Vector3& center);
	Sphere(float radius);
	Sphere(const Vector3& center, float radius);
	Sphere(const Vector3& center, float radius, Material material);

	virtual IntersectionResult Hit(const Ray& ray) override;

	Vector3 Center() const;
	float Radius() const;

	void Center(Vector3 o);
	void Radius(float r);

	friend std::ostream& operator<<(std::ostream& os, const Sphere sphere);
};

