#include "Transform.h"

Transform::Transform() {
	// ���[�J���X�P�[��
	scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	rotation = { 0,0,0 };
	// ���[�J�����W
	position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	matWorld = Affin::matUnit();
}
Transform::~Transform() {}

void Transform::Initialize() {
	// ���[�J���X�P�[��
	scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	rotation = { 0,0,0 };
	// ���[�J�����W
	position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	matWorld = Affin::matUnit();
}