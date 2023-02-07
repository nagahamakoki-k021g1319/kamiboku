#pragma once
#include "Vector3.h"
//#include <DxLib.h>


class Matrix4
{
public:

	float m[4][4];

public:

	// �R���X�g���N�^
	Matrix4();
	Matrix4(float num);
	// �������w�肵�Ă̐���
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	// ������Z�q�I�[�o�[���[�h
	//Matrix4 operator*=(const Matrix4& m2);
	static Matrix4 MakeIdentity()
	{
		Matrix4 mat;
		return mat;
	}
	Vector3 transform(const Vector3& v, const Matrix4& m);
};
// ������Z�q�I�[�o�[���[�h
Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);

// 2�����Z�q�I�[�o�[���[�h
const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
const Vector3 operator*(const Vector3& v, const Matrix4& m2);