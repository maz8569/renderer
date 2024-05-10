#pragma once
#include "Vector3.h"
#include <string>
#include <iostream>

class Ray
{
private:

	Vector3 Origin_;
	Vector3 Destination_;
	Vector3 Direction_;
	float Distance_;

public:

	Ray();
	Ray(Vector3 origin, Vector3	direction);
	Ray(Vector3 origin, float dis);
	Ray(Vector3 origin, Vector3	destination, float dis);

	Vector3 Origin() const;
	Vector3 Destination() const;
	Vector3 Direction() const;
	float Distance() const;

	void Origin(Vector3 o);
	void Destination(Vector3 d);
	void Direction(Vector3 d);
	void Distance(float d);

	friend std::ostream& operator<<(std::ostream& os, const Ray ray);

};

