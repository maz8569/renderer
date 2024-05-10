#include "Material.h"

Material::Material()
{
    Color_ = { 0, 0, 0 };
}

Material::Material(Vector3 color): Color_(color)
{
}

Material::Material(Vector3 color, float specular_amount, float specular_coeff, bool reflect, float refract)
    : Color_(color), specular_amount_(specular_amount), specular_coeff_(specular_coeff), reflect_fraction_(reflect), refract_fraction_(refract)
{
}

Vector3 Material::Color() const
{
    return Color_;
}

void Material::Color(Vector3 color)
{
    Color_ = color;
}
