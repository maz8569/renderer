#include "Plane.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

Plane::Plane() : normal(1, 0, 0), punkt(0, 0, 0)
{
}

Plane::Plane(Vector3 normal_, Vector3 punkt_) : normal(normal_.getNormalized()), punkt(punkt_)
{
}

Plane::Plane(Vector3 normal_, Vector3 punkt_, Material material) : normal(normal_.getNormalized()), punkt(punkt_), Bound(material)
{
}

float Plane::AnglePlane(Plane plane)
{

    Vector3 v4(normal.x, normal.y, normal.z);
    Vector3 v5(plane.normal.x, plane.normal.y, plane.normal.z);
    float dotProduct = v4.dotProduct(v5);
    float l4 = v4.length();
    float l5 = v5.length();
    float cos = dotProduct / (l4 * l5);
    float result = acos(cos) * 180 / M_PI;

    return result;
}

IntersectionResult Plane::Hit(const Ray& ray)
{
    IntersectionResult result;
    float ndotD = normal.dotProduct(ray.Direction());
    
    if (abs(ndotD) < 0.0001f) {
        float check = normal.dotProduct(ray.Origin() - punkt);

        if (check == 0) {

            result.type = IntersectionType::OVERLAP;

        }
        return result;
    }

    float t = ( punkt - ray.Origin()).dotProduct(normal) / ndotD;

    if (t >= 0) {

        result.type = IntersectionType::HIT;
        result.distance = t;
        result.intersectionPoint = ray.Origin() + (ray.Direction() * t);
        result.Normal = normal;
        result.mat = &getMaterial();

        return result;
    }
}

std::ostream& operator<<(std::ostream& strm, const Plane& plane) {

    return strm << plane.normal << " " << plane.punkt ;
}