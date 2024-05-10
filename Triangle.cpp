#include "Triangle.h"

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Material material) : Primitive(material)
{
    v1.z += 2;
    v2.z += 2;
    v3.z += 2;
    _vertices.push_back(v1);
    _vertices.push_back(v2);
    _vertices.push_back(v3);
}

IntersectionResult Triangle::Hit(const Ray& ray)
{
    IntersectionResult result;
    result.type = MISS;
    const float EPSILON = 0.0000001;

    Vector3 edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = _vertices[1] - _vertices[0];
    edge2 = _vertices[2] - _vertices[0];

    h = ray.Direction().cross(edge2);
    a = edge1.dotProduct(h);


    if (a > -EPSILON && a < EPSILON)
        return result;    // This ray is parallel to this triangle.

    f = 1.0 / a;
    s = ray.Origin() - _vertices[0];
    u = f * s.dotProduct(h);
    if (u < 0.0 || u > 1.0)
        return result;
    q = s.cross(edge1);
    v = f * ray.Direction().dotProduct(q);
    if (v < 0.0 || u + v > 1.0)
        return result;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.dotProduct(q);
    if (t > EPSILON) // ray intersection
    {
        result.type = HIT;
        result.distance = t;
        result.intersectionPoint = ray.Origin() + ray.Direction() * t;
    }

    return result;
}
