#include "Ray.h"

Ray::Ray() : Origin_(0, 0, 0), Direction_(0, 0, -1), Distance_(1)
{
}

Ray::Ray(Vector3 origin, Vector3 direction) : Origin_(origin), Direction_(direction.normalize()), Distance_(1)
{
}

Ray::Ray(Vector3 origin, float dis) : Origin_(origin), Direction_(0, 0, -1), Distance_(dis)
{
}

Ray::Ray(Vector3 origin, Vector3 destination, float dis) : Origin_(origin), Destination_(destination), Distance_(dis)
{
	Direction_ = destination - origin;
	Direction_.normalize();
}

Vector3 Ray::Origin() const
{
	return Origin_;
}

Vector3 Ray::Destination() const
{
	return Destination_;
}

Vector3 Ray::Direction() const
{
	return Direction_;
}

float Ray::Distance() const
{
	return Distance_;
}

void Ray::Origin(Vector3 o)
{
	Origin_ = o;
}

void Ray::Destination(Vector3 d)
{
	Destination_ = d;
}

void Ray::Direction(Vector3 d)
{
	Direction_ = d;
}

void Ray::Distance(float d)
{
	Distance_ = d;
}

std::ostream& operator<<(std::ostream& os, const Ray ray)
{
	return os << ray.Origin_ << " " << ray.Direction_ ;
}
