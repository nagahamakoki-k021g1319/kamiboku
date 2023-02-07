//#pragma once
//
////#include "FunctionProcess.h"
//#include "Sprite.h"
//#include "Input.h"
//#include "Matrix4.h"
//#include "Model.h"
//#include "Bullet.h"
//#include "math.h"
//#include <cassert>
//#include <memory>
//#include <list>
//
//#include "View.h"
//#include "Transform.h"
//#include "Object3d.h"
//
//class Player
//{
//public:
//	/// <summary>
//	/// ������
//	/// </summary>
//	/// <param name = "model" > ���f�� </param>
//	/// <param name = "textureHamdle" > �e�N�X�`���n���h�� </param>
//	void Initialize(Model* model,Input* input);
//
//	/// <summary>
//	/// �X�V
//	/// </summary>
//	void Update(View* viewProjection);
//
//	/// <summary>
//	/// �`��
//	/// </summary>
//	void Draw();
//
//	/// <summary>
//	/// UI�`��
//	/// </summary>
//	void DrawUI();
//
//	// ����
//	void Rotate();
//	// �ړ�
//	void Move();
//	// �U��
//	void Attack();
//
//	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
//	void OnCollision();
//
//	void DeleteBullet();
//
//	//�^�}���X�g���擾
//	const std::list<std::unique_ptr<Bullet>>& GetBulletd() { return bullets_; }
//
//	Vector3 RotationOperator(Vector3& velocity, Transform& worldTransform);
//	// ���[���h���W���擾
//	Vector3 GetWorldPosition();
//
//	Matrix4 GetMatrix();
//
//
//private:
//	Input* input_ = nullptr;
//	//DebugText* debugText_ = nullptr;
//	WinApp* winApp_ = nullptr;
//
//	// �r���[�v���_�N�V����
//	//ViewProjection viewProjection_;
//	// ���[���h�ϊ��f�[�^
//	Object3d worldTransform_;
//	// ���f��
//	Model* model_ = nullptr;
//	// �e�N�X�`���n���h��
//	uint32_t textureHandle_ = 0u;
//
//	// �e
//	std::list<std::unique_ptr<Bullet>> bullets_;
//
//	// 3D���e�B�N���p
//	Object3d worldTransform3DReticle_;
//	// 2D���e�B�N���p�X�v���C�g
//	std::unique_ptr<Sprite> sprite2DReticle_;
//};
//
//
