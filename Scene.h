#pragma once
#include "ext.h"
#include <vector>
#include "Light.h"
#include "Bound.h"
#include "Camera.h"

class Scene {
private:

public:
	std::vector<Ref<LightSource>> lights;
	std::vector< Ref<Bound>> objects;

	Ref<Camera> camera;
	int reflectionCount = 2;

	Vector3 Light(IntersectionResult intersection, int intersected, Vector3 rayDir);

};