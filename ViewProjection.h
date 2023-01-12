#pragma once

#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

// �萔�o�b�t�@�p�f�[�^�\����
struct ConstBufferDataViewProjection {
	DirectX::XMMATRIX view;       // ���[���h �� �r���[�ϊ��s��
	DirectX::XMMATRIX projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
	DirectX::XMFLOAT3 cameraPos;  // �J�������W�i���[���h���W�j
};

/// <summary>
/// �r���[�v���W�F�N�V�����ϊ��f�[�^
/// </summary>
struct ViewProjection {
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> constBuff_;
	// �}�b�s���O�ς݃A�h���X
	ConstBufferDataViewProjection* constMap = nullptr;

#pragma region �r���[�s��̐ݒ�
	// ���_���W
	DirectX::XMFLOAT3 eye = { 0, 0, -50.0f };
	// �����_���W
	DirectX::XMFLOAT3 target = { 0, 0, 0 };
	// ������x�N�g��
	DirectX::XMFLOAT3 up = { 0, 1, 0 };
#pragma endregion

#pragma region �ˉe�s��̐ݒ�
	// ������������p
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);
	// �r���[�|�[�g�̃A�X�y�N�g��
	float aspectRatio = (float)16 / 9;
	// �[�x���E�i��O���j
	float nearZ = 0.1f;
	// �[�x���E�i�����j
	float farZ = 1000.0f;
#pragma endregion

	// �r���[�s��
	DirectX::XMMATRIX matView;
	// �ˉe�s��
	DirectX::XMMATRIX matProjection;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �萔�o�b�t�@����
	/// </summary>
	void CreateConstBuffer();
	/// <summary>
	/// �}�b�s���O����
	/// </summary>
	void Map();
	/// <summary>
	/// �s����X�V����
	/// </summary>
	void UpdateMatrix();
};
