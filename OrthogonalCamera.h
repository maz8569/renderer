#pragma once
#include "Camera.h"

class OrthogonalCamera : public Camera
{
private:
	float _l, _r, _b, _t;

public:
	OrthogonalCamera(	Vector3 position, Vector3 target, Vector3 up,
						float l, float r, float b, float t) 
		: Camera(position, target.getNormalized(), up), _l(l), _r(r), _b(b), _t(t) {}

	OrthogonalCamera(OrthogonalCamera *& c) : Camera(*c), _l{ c->_l }, _r{ c->_r }, _b{ c->_b }, _t{ c->_t }{}

	~OrthogonalCamera() {}

	virtual Ray generateRay(float x, float y, unsigned int width, unsigned int height);

};

