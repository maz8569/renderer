#pragma once
#include <string>
#include <iostream>

class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(Vector3 p1, Vector3 p2);
	~Vector3();
	Vector3(const Vector3& v);

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	Vector3 operator+(const Vector3& v);
	Vector3 operator-(const Vector3& v);
	Vector3 operator*(const float& f);
	Vector3 operator*=(const float& f);
	Vector3 operator/(const float& f);
	Vector3 operator/=(const float& f);
	Vector3 operator- () const;

	void div(float f);
	void mult(float f);
	float length();
	Vector3 getNormalized();
	Vector3 normalize();
	float dotProduct(Vector3 v);
	float dot(Vector3 v);
	Vector3 cross(Vector3 v);

	friend Vector3& operator+(const Vector3& v1, const Vector3& v2);
	friend Vector3& operator-(const Vector3& v1, const Vector3& v2);
};

std::ostream& operator<<(std::ostream& strm, const Vector3& v);