#pragma once
#include "Vector3.h"
#include "Matrix4.h"


///<summary>
///�ˉe�s��̍X�V���@�B
///</summary>
enum UpdateProjMatrixFunc
{
	UpdateProjMatrixFunc_Perspective,		//�����ˉe�s��B���ߖ@���������G����肽���Ȃ炱�����B
	UpdateProjMatrixFunc_Ortho,			//���s���e�B�Q�c�I�ȕ\�����������Ȃ炱�����B
};

class Camera
{
public:

	//���_���W
	Vector3 eye = { 0.0f,0.0f,-50.0f };
	//�����_���W
	Vector3 target = { 0.0f,0.0f,0.0f };
	//������x�N�g��
	Vector3 up = { 0.0f,1.0f,0.0f };

private:

	//���_���W
	Vector3 oldEye = eye;
	//�����_���W
	Vector3 oldTarget = target;
	//������x�N�g��
	Vector3 oldUp = up;

	//�r���[�s��
	Matrix4 viewMatrix;
	//�v���W�F�N�V�����s��
	Matrix4 projectionMatrix;
	//�r���[�v���W�F�N�V�����s��
	Matrix4 viewProjectionMatrix;
	//�r���[�s��̋t�s��
	Matrix4 viewMatrixInv;
	//�J�����̉�]�s��
	Matrix4 cameraRotation;

	//��p(���W�A���x)
	float fovAngleY = 0.0;
	//�A�X�y�N�g��(��ʉ���/��ʏc��)
	float aspect = 0.0f;
	//�j�A�N���b�v(�O�[)
	float near_ = 0.0f;
	//�t�@�[�N���b�v(���[)
	float far_ = 0.0f;
	//��ʍ���
	float left = 0.0f;
	//��ʉE�[
	float right = 0.0f;
	//��ʏ㑤
	float top = 0;
	//��ʉ���
	float bottom = 0.0f;

	//�v���W�F�N�V�����s��̍X�V�t���O
	bool updateProjMatrix = true;
	//�r���[�s��̍X�V�t���O
	bool updateViewMatrix = true;
	char PADDING[2]{};

	//�����_�Ǝ��_�̋���
	float tgtToPosLen = 0.0f;

	//�J�����̐��ʃx�N�g��
	Vector3 forward = { 0.0f,0.0f,0.0f };

	
	bool simpleFollowWithWorldUp = false;

	char PADDING2[3]{};


public:

	Camera() = default;
	~Camera() = default;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(UpdateProjMatrixFunc matFunc);

	/// <summary>
	/// �r���[�s��E�v���W�F�N�V�����s����X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �J�����𓮂���
	/// </summary>
	/// <param name="move">��������</param>
	void Move(const AliceMathF::Vector3& move);

	/// <summary>
	/// �����_�𓮂���
	/// </summary>
	/// <param name="move">�ړ���</param>
	void MoveTarget(const AliceMathF::Vector3& move);

	/// <summary>
	/// ���_�𓮂���
	/// </summary>
	/// <param name="move">�ړ���</param>
	void MovePosition(const AliceMathF::Vector3& move);

#pragma region �Z�b�^�[

	/// <summary>
	/// �A�X�y�N�g���ݒ肷��
	/// </summary>
	void SetAspect(float aspect_);

	/// <summary>
	/// �����ʂ܂ł̋�����ݒ�
	/// </summary>
	void SetFar(float fFar);

	/// <summary>
	/// �ߕ��ʂ܂ł̋�����ݒ�
	/// </summary>
	void SetNear(float fNear);

	/// <summary>
	/// �s��̌v�Z���@��ݒ�
	/// </summary>
	/// <param name="func"></param>
	void SetUpdateProjMatrixFunc(UpdateProjMatrixFunc func);

	/// <summary>
	/// ��p��ݒ�
	/// </summary>
	/// <remarks>
	/// SetUpdateProjMatrixFunc��enUpdateProjMatrixFunc_Perspective���ݒ肳��Ă���Ƃ��Ɏg�p�����B
	/// </remarks>
	/// <param name="viewAngle">��p�A�P�ʃ��W�A��</param>
	void SetFovAngleY(float fovAngle);

	/// <summary>
	/// ���s���e�̍��[��ݒ�
	/// </summary>
	/// <param name="left_">���[</param>
	void SetLeft(float left_);

	/// <summary>
	/// ���s���e�̉E�[��ݒ�
	/// </summary>
	/// <param name="right_">�E�[</param>
	void SetRight(float right_);

	/// <summary>
	/// ���s���e�̏�[��ݒ�
	/// </summary>
	/// <param name="top_">��[</param>
	void SetTop(float top_);

	/// <summary>
	/// ���s���e�̉��[��ݒ�
	/// </summary>
	/// <param name="bottom_">���[</param>
	void SetBottom(float bottom_);
#pragma endregion

#pragma region �Q�b�^�[

	/// <summary>
	/// �r���[�s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetViewMatrix();

	/// <summary>
	/// �r���[�s��̋t�s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetViewMatrixInv();

	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetProjectionMatrix();

	/// <summary>
	/// �r���[�~�v���W�F�N�V�����s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetViewProjectionMatrix();

	/// <summary>
	/// �J�����̉�]�s����擾
	/// </summary>
	const AliceMathF::Matrix4& GetCameraRotation();

	/// <summary>
	/// �����ʂ܂ł̋������擾
	/// </summary>
	float GetFar() const;

	/// <summary>
	/// �ߕ��ʂ܂ł̋������擾
	/// </summary>
	float GetNear() const;

	/// <summary>
	/// �A�X�y�N�g����擾
	/// </summary>
	float GetAspect() const;

	/// <summary>
	/// ��p���擾
	/// </summary>
	/// <returns>��p�B�P�ʃ��W�A��</returns>
	float GetFovAngleY() const;

	/// <summary>
	/// �����_�Ǝ��_�̋������擾
	/// </summary>
	/// <returns></returns>
	float GetTargetToPositionLength() const;

	/// <summary>
	/// �J�����̑O�������擾
	/// </summary>
	const AliceMathF::Vector3& GetForward() const;

	/// <summary>
	/// ���s���e�̉��[���擾
	/// </summary>
	float GetBottom();

	/// <summary>
	/// ���s���e�̏�[���擾
	/// </summary>
	float GetTop();

	/// <summary>
	/// ���s���e�̉E�[���擾
	/// </summary>
	float GetRight();

	/// <summary>
	/// ���s���e�̍��[���擾
	/// </summary>
	float GetLeft();

#pragma endregion
};

