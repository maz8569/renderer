#pragma once
#include "Vector3.h"
#include "LightIntensity.h"
#include "Bound.h"
#include <vector>
#include "ext.h"

class LightSource {
private:
	Vector3 position_;
	LightIntensity intensity_;

public:

	LightSource(Vector3 position, LightIntensity intensity) : position_(position), intensity_(intensity) {

	}

	virtual Vector3 getDiffuse() {
		return { 0, 0, 0 };
	};
	virtual Vector3 getSpecular() {
		return { 0, 0, 0 };
	};


	virtual Vector3 Li(std::vector< Ref<Bound>> objects, IntersectionResult intersection, int intersected, Vector3 cameraDir) {
		return { 0, 0, 0 };
	}

	Vector3 Position() const {
		return position_;
	}

	LightIntensity getLightIntensity() const {
		return intensity_;
	}

};