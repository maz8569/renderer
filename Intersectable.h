#pragma once
#include "Ray.h"
#include "IntersectionResult.h"

struct Intersectable {
private:
	Material _material;

public:
	Intersectable() {
		_material = Material();
	}

	Intersectable(Material& material) {
		_material = material;
	}

	virtual IntersectionResult Hit(const Ray& ray) = 0;

	Material& getMaterial() {
		return _material;
	}

	void setMaterial(Material& material) {
		_material = material;
	}
};