#pragma once
#include <vector>
#include "IntersectionResult.h"
#include "Intersectable.h"
#include "Ray.h"

class Primitive : public Intersectable
{
protected:

	std::vector<Vector3> _vertices;
public:

	Primitive() : Intersectable() {

	}

	Primitive(Material& material) : Intersectable(material) {

	}

};

