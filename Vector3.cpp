#include "Vector3.h"

Vector3::Vector3()
{
	x = 1;
	y = 1;
	z = 1;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Vector3 p1, Vector3 p2)
{
	this->x = p1.x + p2.x;
	this->y = p1.y + p2.y;
	this->z = p1.z + p2.z;

}

Vector3::~Vector3()
{
}

Vector3::Vector3(const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

void Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vector3 Vector3::operator+(const Vector3& v)
{
	Vector3 result = *this;

	result += v;

	return result;
}

Vector3 Vector3::operator-(const Vector3& v)
{
	Vector3 result = *this;

	result -= v;

	return result;
}

Vector3 Vector3::operator*(const float& f)
{
	Vector3 result = *this;

	result.mult(f);

	return result;
}

Vector3 Vector3::operator*=(const float& f)
{
	this->mult(f);

	return *this;
}

Vector3 Vector3::operator/(const float& f)
{
	Vector3 result = *this;

	result.div(f);

	return result;
}

Vector3 Vector3::operator/=(const float& f)
{
	this->div(f);

	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

void Vector3::div(float f) {
	if (f != 0) {
		this->x /= f;
		this->y /= f;
		this->z /= f;
	}
	else {
		std::cout << "Can't divide by 0" << std::endl;
	}
}

void Vector3::mult(float f) {
	this->x *= f;
	this->y *= f;
	this->z *= f;
}

float Vector3::length() {
	return (float)sqrt(	pow(this->x, 2) +
						pow(this->y, 2) +
						pow(this->z, 2));
}

Vector3 Vector3::getNormalized() {
	Vector3 result = *this;
	float n = result.length();
	if (n != 0) {
		result.div(n);
	}
	else {
		std::cout << "Can't divide by 0" << std::endl;
	}
	return result;
}

Vector3 Vector3::normalize()
{
	float n = this->length();
	if (n != 0) {
		this->div(n);
	}
	else {
		std::cout << "Can't divide by 0" << std::endl;
	}
	return *this;
}

float Vector3::dotProduct(Vector3 v) {

	Vector3 result;
	//v = v.getNormalized();
	//result = getNormalized();

	result.x = this->x * v.x;
	result.y = this->y * v.y;
	result.z = this->z * v.z;

	return result.x + result.y + result.z;
}

float Vector3::dot(Vector3 v)
{
	Vector3 result;
	v = v.getNormalized();
	result = getNormalized();

	result.x *= v.x;
	result.y *= v.y;
	result.z *= v.z;

	return result.x + result.y + result.z;
}

Vector3 Vector3::cross(Vector3 v) {
	return Vector3(	this->y * v.z - this->z * v.y,
					this->z * v.x - this->x * v.z,
					this->x * v.y - this->y * v.x);
}

Vector3& operator+(const Vector3& v1, const Vector3& v2)
{

	Vector3 result(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);

	return result;
}

Vector3& operator-(const Vector3& v1, const Vector3& v2)
{

	Vector3 result(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);

	return result;
}

std::ostream& operator<<(std::ostream& strm, const Vector3& v) {

	return strm << v.x << " " << v.y << " " << v.z;
}