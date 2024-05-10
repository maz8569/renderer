#pragma once
#include "Vector3.h"
#include "Camera.h"

struct PerspectiveCamera : public Camera
{
	float _nearPlane;
	float _farPlane;
	float _FOV;

	PerspectiveCamera(float nearPlane, float farPlane, float FOV, Vector3 position, Vector3 front = { 0, 0, -1 }, Vector3 up = { 0, 1, 0 })
						: _nearPlane(nearPlane), _farPlane(farPlane), _FOV(FOV), Camera(position, front, up) {}

	virtual Ray generateRay(float x, float y, unsigned int width, unsigned int height);

};

