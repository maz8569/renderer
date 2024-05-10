#include "Scene.h"

Vector3 Scene::Light(IntersectionResult intersection, int intersected, Vector3 rayDir)
{
	Vector3 color = { 0, 0, 0 };

    for(Ref<LightSource> light : lights)
    {
        color += light->Li(objects, intersection, intersected, rayDir);
    }

    if (lights.size() > 0) {
        color /= lights.size();
    }

	return color;
}
