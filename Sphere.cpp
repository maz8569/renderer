#include "Sphere.h"

Sphere::Sphere() : Center_(0, 0, 0), Radius_(1)
{
}

Sphere::Sphere(const Vector3& center) : Center_(center), Radius_(1)
{
}

Sphere::Sphere(float radius) : Center_(0, 0, 0), Radius_(radius)
{
}

Sphere::Sphere(const Vector3& center, float radius) : Center_(center), Radius_(radius)
{
}

Sphere::Sphere(const Vector3& center, float radius, Material material) : Center_(center), Radius_(radius), Bound(material)
{
}

IntersectionResult Sphere::Hit(const Ray& ray)
{
	float t_max = 100.0f, t_min = 0.01f;
	IntersectionResult result;

	float temp = 0.0f;

	Vector3 oc = ray.Origin() - this->Center_;

	float a = ray.Direction().dotProduct(ray.Direction());
	float b = oc.dotProduct(ray.Direction());
	float c = oc.dotProduct(oc) - this->Radius_ * this->Radius_;

	float discriminant = b * b - a * c;

	if (discriminant > 0.001f) 
	{
		temp = (-b - std::sqrtf(discriminant)) / a;

		if (temp <= t_max && temp > t_min) {
			result.type = HIT;
			result.distance = temp;
			result.intersectionPoint = ray.Origin() + ray.Direction() * temp;
			result.Normal = (result.intersectionPoint - Center()).normalize();
			result.mat = &getMaterial();
		}
		/*
		temp = (-b + std::sqrtf(discriminant)) / a;

		if (temp <= t_max && temp > t_min) {
			if(result.type != HIT)
			{
				result.type = HIT;
				result.intersectionPoint = ray.Origin() + ray.Direction() * temp;
			}

		}
		*/
	}

	return	result;

}

Vector3 Sphere::Center() const
{
	return Center_;
}

float Sphere::Radius() const
{
	return Radius_;
}

void Sphere::Center(Vector3 o) 
{
	Center_ = o;
}

void Sphere::Radius(float r) 
{
	Radius_ = r;
}

std::ostream& operator<<(std::ostream& os, const Sphere sphere)
{
	return os << sphere.Center_ << " " << sphere.Radius_ << " ";
}
