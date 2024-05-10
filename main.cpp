// render.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Sphere.h"
#include "Ray.h"
#include <iostream>
#include "Plane.h"
//#include <cmath>
#include "Model.h"
#include "Target.h"
#include "OrthogonalCamera.h"
#include "PerspectiveCamera.h"
#include "Scene.h"
#include <stdlib.h>
#include "PointLight.h"

float RadToDeg(float rad) {
    return rad * (180.0 / 3.141592653589793238463);
}

float randomValue(unsigned int& state) {
    state = state * 747796405 + 2891336453;
    unsigned int result = ((state >> ((state >> 28) + 4)) ^ state) * 277803737;
    result = (result >> 22) ^ result;
    return (float)result / 4294967295.0f;
}

Vector3 Reflect(Vector3 I, Vector3 N)
{
    return I - N * (2 * I.dotProduct(N));
}

Vector3 Refract(Vector3 I, Vector3 N, const float& ior)
{
    float cosi = clamp(-1.0f, 1.0f, I.dotProduct(N));
    float etai = 1, etat = ior;
    Vector3 n = N;
    if (cosi < 0) { cosi = -cosi; }
    else { std::swap(etai, etat); n = -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0) {
        return { 0, 0, 0 };

    }
    else {
        return I * eta + n * (eta * cosi - sqrtf(k));
    }

}

void IntersectScene(Ref<Scene> scene, Ray& nRay, int& b, IntersectionResult& closest, int reflectCount) {
    for (int i = 0; i < scene->objects.size(); i++) {
        Ref<Bound> s = scene->objects[i];
        IntersectionResult res = s->Hit(nRay);
        if (res.type == HIT) {
            if (s->getParent() != nullptr) {
                res.type = MISS;
                res = s->getParent()->render(nRay);
                if (res.type == HIT)
                {
                    if (res.distance < closest.distance)
                        closest = res;

                }
            }
            else {
                if (i != b) {
                    if (res.distance < closest.distance) {
                        closest = res;
                        b = i;
                    }
                }

            }

        }

    }

    for (int k = 0; k < 2; k++) {
        if (closest.mat->refract_fraction_ > 0.001f) {
            nRay = Ray(closest.intersectionPoint, Refract(nRay.Direction(), closest.Normal, closest.mat->refract_fraction_));

            closest.distance = FLT_MAX;
            b = -1;
            IntersectScene(scene, nRay, b, closest, reflectCount);
        }
    }

    if (reflectCount > 0) {
        if (closest.mat->reflect_fraction_) {

            if (closest.intersectionPoint.dotProduct(closest.Normal) < 0) {
                closest.intersectionPoint += closest.Normal * 0.001f;
            }

            nRay = Ray(closest.intersectionPoint, Reflect(nRay.Direction(), closest.Normal));

            closest.distance = FLT_MAX;
            b = -1;
            IntersectScene(scene, nRay, b, closest, reflectCount - 1 );
        }
    }
}

Vector3 getColor(Ref<Scene> scene, float i, float j, int width, int height) {
    Vector3 color = { 0, 0, 0 };
    IntersectionResult closest = IntersectionResult();
    closest.distance = FLT_MAX;
    int b = -1;
    Ray nRay = scene->camera->generateRay(i, j, width, height);
    
    IntersectScene(scene, nRay, b, closest, scene->reflectionCount);

    if (closest.type == HIT) {

        color += scene->Light(closest, b, nRay.Direction().getNormalized());

    }
    else
    {
        color += {  122, 122, 122};
    }

    return color;
}

Vector3 subdiv(int i, int j, int width, int height, Ref<Scene> scene, int maxsubdivs, float centerX, float centerY, float offset) {
    std::vector<Vector3> tempColors;
    Vector3 color = { 0, 0, 0 };
    Vector3 centerColor = { 0, 0, 0 };
    tempColors.clear();

    centerColor = getColor(scene, i + centerX, j + centerY, width, height);
    tempColors.push_back(getColor(scene, i + (centerX - offset), j + (centerY - offset), width, height));
    tempColors.push_back(getColor(scene, i + (centerX + offset), j + (centerY - offset), width, height));
    tempColors.push_back(getColor(scene, i + (centerX - offset), j + (centerY + offset), width, height));
    tempColors.push_back(getColor(scene, i + (centerX + offset), j + (centerY + offset), width, height));

    if (maxsubdivs > 1) {
        if (tempColors[0].x - centerColor.x > 20 || tempColors[0].y - centerColor.y > 20 || tempColors[0].z - centerColor.z > 20) {
            tempColors[0] = subdiv(i, j, width, height, scene, maxsubdivs - 1, -offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColors[0] = (Vector3)(tempColors[0] + centerColor) * 0.5;
        }

        if (tempColors[1].x - centerColor.x > 20 || tempColors[1].y - centerColor.y > 20 || tempColors[1].z - centerColor.z > 20) {
            tempColors[1] = subdiv(i, j, width, height, scene, maxsubdivs - 1, +offset * 0.5f, -offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColors[1] = (Vector3)(tempColors[1] + centerColor) * 0.5;
        }

        if (tempColors[2].x - centerColor.x > 20 || tempColors[2].y - centerColor.y > 20 || tempColors[2].z - centerColor.z > 20) {
            tempColors[2] = subdiv(i, j, width, height, scene, maxsubdivs - 1, -offset * 0.5f, +offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColors[2] = (Vector3)(tempColors[2] + centerColor) * 0.5;
        }

        if (tempColors[3].x - centerColor.x > 20 || tempColors[3].y - centerColor.y > 20 || tempColors[3].z - centerColor.z > 20) {
            tempColors[3] = subdiv(i, j, width, height, scene, maxsubdivs - 1, +offset * 0.5f, +offset * 0.5f, offset * 0.5f);
        }
        else {
            tempColors[3] = (Vector3)(tempColors[3] + centerColor) * 0.5;
        }
    }


    for (auto c : tempColors) {
        color += c;
    }

    color = color / tempColors.size();

    return color;
}

void RenderScene(TGABuffer& target, Ref<Scene> scene, int max) {
    int maxSub = 2;
    int forProgress = 0;
    Vector3 color = { 0, 0, 0 };
    for (int i = 0; i < target.getWidth(); i++) {
        if (i % (target.getWidth() / 10) == 0) {
            system("CLS");
            std::cout << forProgress <<"0% gotowe\n";
            forProgress++;
        }
        
        for (int j = 0; j < target.getHeight(); j++) {
            maxSub = max;

            color = subdiv(i, j, target.getWidth(), target.getHeight(), scene, maxSub, 0.0f, 0.0f, 0.5f);

            target.setPixel(i, j, TGABuffer::GetColorFromRGB(color.x, color.y, color.z));
        }
    }
}

int main()
{
    //Model cube("models/hat/hat.obj");
    //cube.bounds = Sphere({ 0, 0, 2 }, 0.8, { 0, 0, 255 });

    //cube.bounds.setParent(&cube);

    TGABuffer target = TGABuffer(1024, 1024);
    target.ClearColor(10, 100, 200);
    
    Ref<Sphere> S = CreateRef<Sphere>(Vector3(-0.4, 0, 2), 0.6, Material({255, 0, 0}, 12, 1));
    Ref<Sphere> S2 = CreateRef<Sphere>(Vector3(0.3, -0.1, 1), 0.5, Material({ 0, 255, 0 }, 1024, 1, false, 0.69f));
    Ref<Plane> P1 = CreateRef<Plane>(Vector3(-1, 0, 0 ), Vector3(4, 0, 0 ), Material({125, 125, 255}, 128, 1, true));
    Ref<Plane> P2 = CreateRef<Plane>(Vector3(1, 0, 0 ), Vector3(-4, 0, 0 ), Material({125, 125, 255}, 128, 1, true));
    Ref<Plane> P3 = CreateRef<Plane>(Vector3(0, -1, 0 ), Vector3(0, 4, 0 ), Material({255, 125, 125}, 128, 1));
    Ref<Plane> P4 = CreateRef<Plane>(Vector3(0, 1, 0 ), Vector3(0, -4, 0 ), Material({255, 125, 125}, 128, 1));
    Ref<Plane> P5 = CreateRef<Plane>(Vector3(0, 0, -1 ), Vector3(0, 0, 8 ), Material({255, 255, 255}));
    Ref<Plane> P6 = CreateRef<Plane>(Vector3(0, 0, 1 ), Vector3(0, 0, -8 ), Material({0, 0, 0}));
    Ref<OrthogonalCamera> ocamera = CreateRef<OrthogonalCamera>(Vector3(0, 0, -1 ), Vector3(0, 0, 2 ), Vector3(0, 1, 0 ), 20, 20, 20, 20);
    Ref<PerspectiveCamera> pcamera = CreateRef<PerspectiveCamera>(0.1f, 100, 90.0f, Vector3(0, 0, -1 ), Vector3(0, 0, -10 ), Vector3(0, -1, 0 ));

    target.ClearColor(10, 100, 200);

    Ref<Scene> scene = CreateRef<Scene>();

    //std::vector<Bound* > spheres;
    scene->objects.push_back(S);
    scene->objects.push_back(CreateRef<Sphere>(Vector3(1, 1, 3), 0.5, Material({ 0, 255, 0 }, 1024, 1, true, 0.0f)));
    //scene->objects.push_back(CreateRef<Sphere>(Vector3(-1, 1, 1), 0.2, Material({ 0, 255, 0 }, 1024, 1, true, 0.0f)));
    //scene->objects.push_back(CreateRef<Sphere>(Vector3(0, 1, 3), 0.5, Material({ 0, 255, 0 }, 1024, 1, false, 1.5f)));
    scene->objects.push_back(S2);
    scene->objects.push_back(P1);
    scene->objects.push_back(P2);
    scene->objects.push_back(P3);
    scene->objects.push_back(P4);
    scene->objects.push_back(P5);
    scene->objects.push_back(P6);

    scene->camera = pcamera;

    scene->lights.push_back(CreateRef<PointLight>(Vector3(0, 1, 0), LightIntensity(1.0, 1.0, 1.0), 1, 0.05, 0.012));
    //scene->lights.push_back(CreateRef<PointLight>(Vector3(1, 0, 3), LightIntensity(1.0, 0.88, 0.83), 1, 0.05, 0.012));
    //scene->lights.push_back(CreateRef<PointLight>(Vector3(-2, 0, 0), LightIntensity(1.0, 0.0, 0.0), 1, 0.05, 0.012));

    //spheres.push_back(&cube.bounds);
    
    
    //RenderSpheres(target, ocamera, spheres, 2);

    //target.Save("out01");
    //std::cout << "ortho saved \n";

    RenderScene(target, scene, 3);

    target.Save("out01");
    std::cout << "perspective saved \n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// TODO: 
///   Proszę zaimplementować klasy obrazu, natężenia i kamery (ortogonalną oraz perpsektywiczną), a następnie wyrenderować obraz, zawierający dwie kule. wykorzystując rzut perspektywiczny i rzut ortogonalny. Należy zaimplementować podaną metodą antyaliasingu adaptacyjnego lub własną, zaproponowaną metodę.

/// Proszę zaimplementować klasę trójkąta, będącą konkretyzacją klasy abstrakcyjnej prymityw, zawierającą dowolny algorytm obliczania przecięcia promienia z trójkątem, a następnie zdefiniować klasę siatki geometrycznej(mesh) zawierającej listę trójkątów.% Proszę stworzyć w programie prosty parser formatu OBJ.

/// Na tym etapie, program powinien umożliwiać rendering sceny zawierającej, oprócz sfery i płaszczyzny, dowolny ostrosłup wczytany z pliku OBJ.
