#include "PerspectiveCamera.h"
#define M_PI 3.14159265358979323846

Ray PerspectiveCamera::generateRay(float x, float y, unsigned int width, unsigned int height)
{
	
	float FOVY = _FOV * M_PI / 360;
	float PX = (2 * ((x + 0.5f) / width) - 1) * (width / height) * tan(FOVY);
	float PY = (1 - 2 * ((y + 0.5f) / height)) * tan(FOVY);
	/*
	Vector3 dir = Vector3(PX, PY, -1) - this->_position;
	dir.normalize();
	*/

	float fLenght = sin(90 - FOVY) / sin(FOVY);

	Vector3 gaze = this->_target - this->_position;

	Vector3 w = gaze * -1;
	w.normalize();

	Vector3 sx = w.cross(_up);
	sx.normalize();
	//sx = sx * tan(FOVY);

	Vector3 sy = sx.cross(w);
	sy.normalize();
	//sy = sy * tan(FOVY);

	float ww = tan(FOVY);

	Vector3 dir = sx * PX + sy * PY;
	dir = dir + w * fLenght;

	dir.normalize();

	//std::cout << dir << "\n";

	return Ray(this->_position, dir);
}
