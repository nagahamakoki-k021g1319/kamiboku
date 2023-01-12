#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3D�I�u�W�F�N�g���
	delete homeOBJ;
	delete player;

	//3D���f�����
	delete model;
	delete model2;

	//�I�[�f�B�I���
	audio->Finalize();
	delete audio;

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//�X�v���C�g�̏�����
	{
		sprite->Initialize(spriteCommon);
		position.x = 400.0f;
		position.y = 0.0f;
		sprite->SetPozition(position);
		sprite->SetSize(XMFLOAT2{ 500.0f,281.0f });

		sprite1->Initialize(spriteCommon);
		sprite1->SetPozition(position1);
		sprite1->SetSize(XMFLOAT2{ 200.0f,112.0f });

		sprite2->Initialize(spriteCommon);
		position2.x = 900.0f;
		sprite2->SetPozition(position2);
		sprite2->SetSize(XMFLOAT2{ 300.0f,170.0f });
	}
	//�X�v���C�g�̉摜�w��
	{
		spriteCommon->LoadTexture(0, "eri.png");
		sprite->SetTextureIndex(0);
		spriteCommon->LoadTexture(1, "feri.png");
		sprite1->SetTextureIndex(1);
		spriteCommon->LoadTexture(2, "ynkm.png");
		sprite2->SetTextureIndex(2);
	}
	// OBJ���烂�f���f�[�^��ǂݍ���
	{
		model = Model::LoadFromOBJ("as");
		model2 = Model::LoadFromOBJ("as2");
		zangoMD = Model::LoadFromOBJ("zango");
	}
	//3D�I�u�W�F�N�g����
	{
		homeOBJ = Object3d::Create();
		player = Object3d::Create();
		zango = Object3d::Create();
	}
	// �e�q�ݒ�
	{
		player->SetParent(homeOBJ);
	}
	// �I�u�W�F�N�g�Ƀ��f����R�Â���
	{
		homeOBJ->SetModel(model);
		player->SetModel(model2);
		zango->SetModel(zangoMD);
	}
	//3D�I�u�W�F�N�g�̈ʒu���w��
	{
		player->SetPosition({ 0,0,10 });
		zango->SetScale({ 5,3.5f,5 });
	}


	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("cr.wav");
	audio->LoadWave("tit.wav");

	
}


void GameScene::Update() {
	// �I�u�W�F�N�g�ړ�
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// ���݂̍��W���擾
		XMFLOAT3 rotate = homeOBJ->GetRotate();

		// �ړ���̍��W���v�Z
		if (input->PushKey(DIK_UP)) { rotate.y += 0.5f; }
		else if (input->PushKey(DIK_DOWN)) { rotate.y -= 0.5f; }
		/*	if (input->PushKey(DIK_RIGHT)) { rotate.x += 1.0f; }
			else if (input->PushKey(DIK_LEFT)) { rotate.x -= 1.0f; }*/

			// ���W�̕ύX�𔽉f

		homeOBJ->SetRotate(rotate);
	}
	homeOBJ->Update();
	player->Update();
	zango->Update();



	//�����蔻��
	XMFLOAT3 a = player->GetPosition();
	XMFLOAT3 b = homeOBJ->GetPosition();
	float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
	float lenR = std::pow(1.0f + 1.0f, 2.0f);
	if (xyz <= lenR) {
		ischackFlag = 1;
	}
	// ���Z�b�g
	if (input->PushKey(DIK_R)) {
		ischackFlag = 0;
	}


	//�����Đ�
	if (soundCheckFlag == 0) {
		//�����Đ�
		audio->PlayWave("tit.wav");
		soundCheckFlag = 1;
	}
	if (input->TriggerKey(DIK_SPACE)) {
		//�����Đ�
		audio->PlayWave("cr.wav");
	}


}

void GameScene::Draw() {
	sprite->Draw();

	if (ischackFlag == 0) {
		sprite1->Draw();
	}
	else {}

	sprite2->Draw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>

	//3D�I�u�W�F�N�g�̕`��
	homeOBJ->Draw();
	player->Draw();
	zango->Draw();


	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();


}