#pragma once
#include "Vector3.h"
#include "Ray.h"

class Camera
{
protected:
	Vector3 _position;
	Vector3 _target;
	Vector3 _up;

public:

	Camera(Vector3 position, Vector3 target, Vector3 up = {0, 1, 0}) : _position(position), _target(target), _up(up) {}
	virtual ~Camera() {}

	virtual Ray generateRay(float x, float y, unsigned int width, unsigned int height) { return Ray(Vector3(x, y, 1), Vector3(x, y, 1), 0); }

	Vector3 Position() const {
		return _position;
	}
	Vector3 getDirection() const {
		return _target;
	}

};

