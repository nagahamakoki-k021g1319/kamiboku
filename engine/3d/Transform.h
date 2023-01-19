#pragma once

#include "Matrix4.h"
#include "Affin.h"

class Transform
{
public:
	Transform();
	~Transform();
	void Initialize();
public:
	// ���[�J���X�P�[��
	Vector3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	Vector3 rotation = { 0,0,0 };
	// ���[�J�����W
	Vector3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	Matrix4 matWorld = Affin::matUnit();

};