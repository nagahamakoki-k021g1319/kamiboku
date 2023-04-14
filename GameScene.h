#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include <string>
#include "ParticleManager.h"
#include "DebugCamera.h"
#include "FBXObject3d.h"
#include "FbxLoader.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	//FBX�Ŏg���J����(�r���[�v���W�F�N�V����?�݂�����)
	DebugCamera* camera = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;
	

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	Sprite* sprite = new Sprite();
	XMFLOAT2 position = sprite->GetPosition();

	Sprite* sprite1 = new Sprite();
	XMFLOAT2 position1 = sprite1->GetPosition();

	Sprite* sprite2 = new Sprite();
	XMFLOAT2 position2 = sprite2->GetPosition();

	Sprite* sprite3 = new Sprite();
	XMFLOAT2 position3 = sprite3->GetPosition();

	Sprite* sprite4 = new Sprite();
	XMFLOAT2 position4 = sprite4->GetPosition();

	Sprite* sprite5 = new Sprite();
	XMFLOAT2 position5 = sprite5->GetPosition();

	Sprite* sprite6 = new Sprite();
	XMFLOAT2 position6 = sprite6->GetPosition();

	Sprite* sprite7 = new Sprite();
	XMFLOAT2 position7 = sprite7->GetPosition();

	Sprite* sprite8 = new Sprite();
	XMFLOAT2 position8 = sprite8->GetPosition();

	Sprite* sprite9 = new Sprite();
	XMFLOAT2 position9 = sprite9->GetPosition();

	Sprite* sprite10 = new Sprite();
	XMFLOAT2 position10 = sprite10->GetPosition();

	Sprite* sprite11 = new Sprite();
	XMFLOAT2 position11 = sprite11->GetPosition();

	Sprite* sprite12 = new Sprite();
	XMFLOAT2 position12 = sprite12->GetPosition();

	Sprite* sprite13 = new Sprite();
	XMFLOAT2 position13 = sprite13->GetPosition();

	Sprite* sprite14 = new Sprite();
	XMFLOAT2 position14 = sprite14->GetPosition();

	int ischackFlag = 0;

	Object3d* object3d = nullptr;
	Object3d* object3d_2 = nullptr;
	Object3d* object3d_3 = nullptr;

	Model* model = nullptr;
	Model* model2 = nullptr;
	Model* model3 = nullptr;


	int soundCheckFlag[10] = {0};
	
	//�p�[�e�B�N���N���X�̏����� 
	ParticleManager* particleManager = nullptr;

	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;

	FBXModel* fbxModel2_ = nullptr;
	FBXObject3d* fbxObject3d_2 = nullptr;

	int isDrornFlag = 0;
	int isChangeDrornTimer = 0;

	int isLeftFlag = 0;
	int isRightFlag = 0;


	int isSHFlag = 0;
	int SHtimer = 0;

public:
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

};

