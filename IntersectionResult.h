#pragma once
#include "Material.h"

enum IntersectionType {
	MISS,
	HIT,
	OVERLAP
};

struct IntersectionResult
{
	IntersectionType type = MISS;
	float distance = 0.0f;
	Vector3 intersectionPoint = Vector3(0, 0, 0);
	Vector3 Normal = Vector3(0, 0, 0);
	Material* mat = nullptr;
};

