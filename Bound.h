#pragma once
#include "Ray.h"
#include "IntersectionResult.h"
#include "Intersectable.h"

class Model;

class Bound : public Intersectable
{
private:
	Model* Parent_ = nullptr;

public:

	Bound();
	Bound(Material& material);

	virtual IntersectionResult Hit(const Ray& ray);

	virtual void setParent(Model* parent);
	virtual Model* getParent();
};

