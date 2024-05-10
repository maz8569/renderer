#include "LightIntensity.h"

void LightIntensity::add(double R, double G, double B)
{
	r += R;
	g += G;
	b += B;
}

LightIntensity LightIntensity::operator+(LightIntensity& li)
{
	return LightIntensity(this->r + li.r, this->g + li.g, this->b + li.b);
}

LightIntensity LightIntensity::operator-(LightIntensity& li)
{
	return LightIntensity(this->r - li.r, this->g - li.g, this->b - li.b);
}

LightIntensity LightIntensity::operator/(float num)
{
	return LightIntensity(this->r / num, this->g / num, this->b / num);
}

LightIntensity LightIntensity::operator+=(LightIntensity& li)
{
	this->r += li.r;
	this->g += li.g;
	this->b += li.b;

	return *this;
}

LightIntensity LightIntensity::operator-=(LightIntensity& li)
{
	this->r -= li.r;
	this->g -= li.g;
	this->b -= li.b;

	return *this;
}

LightIntensity LightIntensity::operator*=(float num)
{
	this->r *= num;
	this->g *= num;
	this->b *= num;

	return *this;
}

LightIntensity LightIntensity::operator/=(float num)
{
	this->r /= num;
	this->g /= num;
	this->b /= num;

	return *this;
}

LightIntensity operator*(float num, LightIntensity& li)
{
	return LightIntensity(li.r * num, li.g * num, li.b * num);
}

LightIntensity operator*(LightIntensity& li, float num)
{
	return LightIntensity(li.r * num, li.g * num, li.b * num);
}

std::ostream& operator<<(std::ostream& str, LightIntensity& li)
{
	return str << "Light intensity: r - " << li.r << ", g - " << li.g << ", b - " << li.b;
}
