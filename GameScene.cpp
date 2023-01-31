#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3D�I�u�W�F�N�g���
	delete object3d;
	delete object3d_2;

	//3D���f�����
	delete model;
	delete model2;

	//FBX�I�u�W�F�N�g���
	delete fbxObject3d_;
	delete fbxModel_;

	delete fbxObject3d_2;
	delete fbxModel2_;

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

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	FBXObject3d::SetCamera(camera);


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
	}
	//3D�I�u�W�F�N�g����
	{
		object3d = Object3d::Create();
		object3d_2 = Object3d::Create();
	}
	// �I�u�W�F�N�g�Ƀ��f����R�Â���
	{
		object3d->SetModel(model);
		object3d_2->SetModel(model2);
	}
	//3D�I�u�W�F�N�g�̈ʒu���w��
	{
		object3d_2->SetPosition({ -5,-5,0 });
	}

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("Player");
	fbxModel2_ = FbxLoader::GetInstance()->LoadModelFromFile("Player");

	// �f�o�C�X���Z�b�g
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// �O���t�B�b�N�X�p�C�v���C������
	FBXObject3d::CreateGraphicsPipeline();


	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->SetScale({ 0.01,0.01,0.01 });
	fbxObject3d_->SetPosition({ 0,-10,40 });
	fbxObject3d_->PlayAnimation();

	fbxObject3d_2 = new FBXObject3d;
	fbxObject3d_2->Initialize();
	fbxObject3d_2->SetModel(fbxModel2_);
	fbxObject3d_2->SetScale({ 0.01,0.01,0.01 });
	fbxObject3d_2->SetPosition({ -10,-10,40 });
	fbxObject3d_2->PlayAnimation();



	// �p�[�e�B�N������
	particleManager = ParticleManager::Create();
	particleManager->Update();

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("cr.wav");
	audio->LoadWave("tit.wav");

	
}


void GameScene::Update() {
	//�����Đ�
	if (soundCheckFlag == 0) {
		//�����Đ�
		pSourceVoice[0] = audio->PlayWave("tit.wav");
		soundCheckFlag = 1;
	}
	if (input->TriggerKey(DIK_E)) {
		pSourceVoice[0]->Stop();
	}
	if (input->TriggerKey(DIK_Z)) {
		pSourceVoice[0]->SetVolume(0.1f);
	}if (input->TriggerKey(DIK_X)) {
		pSourceVoice[0]->SetVolume(1.0f);
	}


	if (input->TriggerKey(DIK_SPACE)) {
		//�����Đ�
		audio->PlayWave("cr.wav");
	}
	camera->Update();
	object3d->Update();
	// �I�u�W�F�N�g�ړ�
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = object3d->GetPosition();

		// �ړ���̍��W���v�Z
		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		// ���W�̕ύX�𔽉f
		object3d->SetPosition(position);
	}

	object3d_2->Update();

	//�����蔻��
	XMFLOAT3 a = object3d_2->GetPosition();
	XMFLOAT3 b = object3d->GetPosition();
	float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
	float lenR = std::pow(1.0f + 1.0f, 2.0f);
	if (xyz <= lenR) {
		ischackFlag = 1;
	}
	// ���Z�b�g
	if (input->PushKey(DIK_R)) {
		ischackFlag = 0;
	}

	// �p�[�e�B�N���N��(������)
	if (input->PushKey(DIK_P)) {
		particleManager->Update();
		//�p�[�e�B�N���͈�
		for (int i = 0; i < 20; i++) {
			//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
			const float rnd_pos = 10.0f;
			//const float rnd_posX = 1.0f;
			XMFLOAT3 pos{};
			pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
			pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

			//���x
			//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
			const float rnd_vel = 0.5f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
			const float rnd_acc = 0.001f;
			XMFLOAT3 acc{};
			acc.y = (float)rand() / RAND_MAX * rnd_acc;

			//�ǉ�
			particleManager->Add(60, pos, vel, acc, 1.0f, 0.0f);
		}
	}

	fbxObject3d_->Update();
	fbxObject3d_2->Update();


	


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
	object3d->Draw();
	object3d_2->Draw();

	fbxObject3d_->Draw(dxCommon->GetCommandList());
	fbxObject3d_2->Draw(dxCommon->GetCommandList());





	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// 3D�I�u�W�F�N�g�`��O����
	ParticleManager::PreDraw(dxCommon->GetCommandList());

	// 3D�I�u�N�W�F�N�g�̕`��
	particleManager->Draw();

	// 3D�I�u�W�F�N�g�`��㏈��
	ParticleManager::PostDraw();
}