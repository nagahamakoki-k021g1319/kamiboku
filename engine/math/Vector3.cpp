#include "Vector3.h"

#include <DirectXMath.h>
#include <cmath>

using namespace DirectX;


Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector3::length()const {

	return (sqrt(x) * sqrt(x)) + (sqrt(y) * sqrt(y)) + (sqrt(z) * sqrt(z));
}

Vector3& Vector3::nomalize() {
	float len = length();
	if (len != 0) {
		return *this /= len;
	}
	return *this;
}

float Vector3::dot(const Vector3& v) const {
	return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

Vector3 Vector3::cross(const Vector3& v) const {
	Vector3 w;
	w.x = y * v.z - z * v.y;
	w.y = z * v.x - x * v.z;
	w.z = x * v.y - y * v.x;

	return w;
}

const Vector3 Vector3::lerp(const Vector3& start, const Vector3& end, const float t) {
	/*float y = t;
	return start * (1.0f - y) + end * y;*/
	return start * (1.0f - t) + end * t;
}

Vector3 Vector3::operator+()const {
	return *this;
}

Vector3 Vector3::operator-()const {
	return Vector3(-(*this));         ////
}

Vector3& Vector3::operator+=(const Vector3& v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector3& Vector3::operator*=(float s) {
	this->x *= s;
	this->y *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s) {
	this->x /= s;
	this->y /= s;
	return *this;
}

//Vector2D　クラスに属さない関数群
//二項演算子
const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v) {
	return s * v;
}

const Vector3 operator/(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp / s;
}

// XM用

//Vector3& Vector3::operator=(const XMFLOAT3& v1) {
//	Vector3 res;
//
//	res.x = v1.x;
//	res.y = v1.y;
//	res.z = v1.z;
//
//	return res;
//}

//XMFLOAT3& Vector3::operator=(const Vector3& v) {
//	XMFLOAT3 res;
//
//	res.x = v.x;
//	res.y = v.y;
//	res.z = v.z;
//
//	return res;
//}