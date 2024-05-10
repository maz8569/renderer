#include "Bound.h"

Bound::Bound() : Intersectable()
{
}

Bound::Bound(Material& material) : Intersectable(material)
{
}

IntersectionResult Bound::Hit(const Ray& ray)
{
	return IntersectionResult();
}

void Bound::setParent(Model* parent)
{
	Parent_ = parent;
}

Model* Bound::getParent()
{
	return Parent_;
}
