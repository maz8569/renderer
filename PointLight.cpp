#include "PointLight.h"
#include "Ray.h"
#include "IntersectionResult.h"

PointLight::PointLight(Vector3 position, LightIntensity intensity, float constant, float linear, float quadratic) : LightSource(position, intensity),
                                                                                                                    constant_(constant), linear_(linear), quadratic_(quadratic)
{
}

Vector3 PointLight::Li(std::vector< Ref<Bound>> objects, IntersectionResult intersection, int intersected, Vector3 cameraDir)
{

    bool shadow = false;
    float dist = (Position() - intersection.intersectionPoint).length();

    Ray nRay = Ray(Position(), intersection.intersectionPoint, 0);
    for (int i = 0; i < objects.size(); i++) {
        Ref<Bound> s = objects[i];
        IntersectionResult res = s->Hit(nRay);
        if (res.type == HIT) {
            if (dist - res.distance > 0.1f && intersected != i) {
                shadow = true;
                break;
            }
        }
    }
    Vector3 color = intersection.mat->Color();
    Vector3 ambient = color * 0.2f;

    ambient.x *= getLightIntensity().gRed();
    ambient.y *= getLightIntensity().gGreen();
    ambient.z *= getLightIntensity().gBlue();

    if (shadow) {
        color = ambient;
    }
    else {
        Vector3 l = (Position() - intersection.intersectionPoint).getNormalized();

        float shade = intersection.Normal.dotProduct(l);
        float attenuation = 1.0 / (constant_ + linear_ * dist + quadratic_ * (dist * dist));

        //Vector3 halfwayDir = (l + cameraDir).normalize();
        //float spec = pow(std::max(halfwayDir.dotProduct(intersection.Normal), 0.0f), intersection.mat->specular_amount_);

        Vector3 R = l - (intersection.Normal * intersection.Normal.dotProduct(l) * 2.0f);
        float ss = -cameraDir.dotProduct(R);
        float sp = -cameraDir.dotProduct(R);
        float spec = 0;

        if (-ss > 0) {
            spec = pow(ss, intersection.mat->specular_amount_);
        }

        spec *= intersection.mat->specular_coeff_;

        shade = clamp(shade * attenuation, 0.2f, 1.0f);
        color.x *= shade * getLightIntensity().gRed();
        color.y *= shade * getLightIntensity().gGreen();
        color.z *= shade * getLightIntensity().gBlue();

        Vector3 specular = color;
        specular.x *= spec * getLightIntensity().gRed();
        specular.y *= spec * getLightIntensity().gGreen();
        specular.z *= spec * getLightIntensity().gBlue();

        color += specular;

    }
    color.x = clamp(color.x, 0.0f, 255.0f);
    color.y = clamp(color.y, 0.0f, 255.0f);
    color.z = clamp(color.z, 0.0f, 255.0f);
    return color;
}
