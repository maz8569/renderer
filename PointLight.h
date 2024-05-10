#pragma once
#include "Light.h"

class PointLight :
    public LightSource
{
private:

    float constant_;
    float linear_;
    float quadratic_;

public:

    PointLight(Vector3 position, LightIntensity intensity, float constant, float linear, float quadratic);
    virtual Vector3 Li(std::vector< Ref<Bound>> objects, IntersectionResult intersection, int intersected, Vector3 cameraDir) override;
};

