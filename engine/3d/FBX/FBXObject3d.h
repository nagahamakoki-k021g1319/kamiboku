#pragma once
#include "FBXModel.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include "FbxLoader.h"

#include "Transform.h"
#include "Affin.h"
#include "ConvertXM.h"


class FBXObject3d
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	/*using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;*/

public: // �T�u�N���X
// �萔�o�b�t�@�p�f�[�^�\���́i���W�ϊ��s��p�j
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;    // �r���[�v���W�F�N�V�����s��
		XMMATRIX world; // ���[���h�s��
		XMFLOAT3 cameraPos; // �J�������W�i���[���h���W�j
	};
	//�{�[���̍ő吔
	static const int MAX_BONES = 32;

	//�萔�o�b�t�@�p�̃f�[�^�\����(�X�L�j���O)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};


public: // �ÓI�����o�֐�
	/// <summary>
	/// �O���t�B�b�N�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();
	
	/// <summary>
	/// �O���t�B�b�N�p�C�v���C���̐���
	/// </summary>
	// setter
	static void SetDevice(ID3D12Device* device) { FBXObject3d::device = device; }
	static void SetCamera(Camera* camera) { FBXObject3d::camera = camera; }


private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �J����
	static Camera* camera;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;


public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);


	/// <summary>
	/// �f�J���̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetScale(const Vector3& scale) { this->wtf.scale = scale; }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const Vector3& position) { this->wtf.position = position; }


	void SetModel(FBXModel* fbxmodel) { this->fbxmodel = fbxmodel; }

	/// <summary>
	/// �A�j���[�V�����J�n
	/// </summary>
	void PlayAnimation();

	Transform wtf;
	
protected: // �����o�ϐ�
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	// �萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBuffSkin;
	//// ���[�J���X�P�[��
	//XMFLOAT3 scale = { 1,1,1 };
	//// X,Y,Z�����̃��[�J����]�p
	//XMFLOAT3 rotation = { 0,0,0 };
	//// ���[�J�����W
	//XMFLOAT3 position = { 0,0,0 };
	//// ���[�J�����[���h�ϊ��s��
	//XMMATRIX matWorld;
	// ���f��
	FBXModel* fbxmodel = nullptr;

	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���(�A�j���[�V����)
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;
};

