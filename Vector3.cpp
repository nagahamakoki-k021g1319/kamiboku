#include "Vector3.h"
#include <cmath>

Vector3::Vector3()
	:x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

float Vector3::length()const {
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector3& Vector3::nomalize() {
	float len = length();
	if (len != 0) {
		return *this /= length();
	}
	return *this;
}

float Vector3::dot(const Vector3& v)const {
	return(x * v.x) + (y * v.y) + (z * v.z);
}

Vector3 Vector3::cross(const Vector3& v)const {
	Vector3 ans;

	ans = { (y * v.z) - (z * v.y),(z * v.x) - (x * v.z), (x * v.y) - (y * v.x) };

	return ans;
}

const Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, const float t) {
	/*float y = t;
	return start * (1.0f - y) + end * y;*/
	return start * (1.0f - t) + end * t;
}

Vector3 Vector3::Vector3Zero() {
	Vector3 a = { 0, 0, 0 };
	return a;
}

bool Vector3::Vector3Equal(Vector3 v1, Vector3 v2) {
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z) {
		return true;
	}
	else
	{
		return false;
	}
}
bool Vector3::Vector3IsInfinite() {
	if (isfinite(this->x) && isfinite(this->y) && isfinite(this->z)) {
		return true;
	}
	else {
		return false;
	}
}

Vector3 Vector3::operator+()const {
	return *this;
}

Vector3 Vector3::operator-()const {
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return*this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return*this;
}

Vector3& Vector3::operator*=(float s) {
	x *= s;
	y *= s;
	z *= s;
	return*this;
}

Vector3& Vector3::operator/=(float s) {
	x /= s;
	y /= s;
	z /= s;
	return*this;
}

//Vector3?N???X????????????Q
//2?????Z?q
const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp += v2;
}
const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 tenp(v1);
	return tenp -= v2;
}

const Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v) {
	return v * s;
}

const Vector3 operator/(const Vector3& v, float s) {
	Vector3 temp(v);
	return v / s;
}