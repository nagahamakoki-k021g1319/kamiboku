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
		sprite1->SetSize(XMFLOAT2{ 100.0f,100.0f });

		sprite2->Initialize(spriteCommon);
		position2.x = 100.0f;
		sprite2->SetPozition(position2);
		sprite2->SetSize(XMFLOAT2{ 300.0f,170.0f });

		sprite3->Initialize(spriteCommon);
		position3.x = 50.0f;
		position3.y = 600.0f;
		sprite3->SetPozition(position3);
		sprite3->SetSize(XMFLOAT2{ 50.0f,35.0f });

		sprite4->Initialize(spriteCommon);
		position4.x = 50.0f;
		position4.y = 600.0f;
		sprite4->SetPozition(position4);
		sprite4->SetSize(XMFLOAT2{ 50.0f,35.0f });

		sprite5->Initialize(spriteCommon);
		position5.x = 100.0f;
		position5.y = 600.0f;
		sprite5->SetPozition(position5);
		sprite5->SetSize(XMFLOAT2{ 50.0f,35.0f });

		sprite6->Initialize(spriteCommon);
		position6.x = 100.0f;
		position6.y = 600.0f;
		sprite6->SetPozition(position6);
		sprite6->SetSize(XMFLOAT2{ 50.0f,35.0f });

		sprite7->Initialize(spriteCommon);
		position7.x = 1150.0f;
		position7.y = 30.0f;
		sprite7->SetPozition(position7);
		sprite7->SetSize(XMFLOAT2{ 100.0f,100.0f });

		sprite8->Initialize(spriteCommon);
		position8.x = 300.0f;
		position8.y = 500.0f;
		sprite8->SetPozition(position8);
		sprite8->SetSize(XMFLOAT2{ 50.0f,50.0f });

		sprite9->Initialize(spriteCommon);
		position9.x = 800.0f;
		position9.y = 500.0f;
		sprite9->SetPozition(position9);
		sprite9->SetSize(XMFLOAT2{ 70.0f,50.0f });

		sprite10->Initialize(spriteCommon);
		position10.x = 500.0f;
		position10.y = 500.0f;
		sprite10->SetPozition(position10);
		sprite10->SetSize(XMFLOAT2{ 200.0f,112.0f });

		sprite11->Initialize(spriteCommon);
		position11.x = 500.0f;
		position11.y = 500.0f;
		sprite11->SetPozition(position11);
		sprite11->SetSize(XMFLOAT2{ 200.0f,112.0f });

		sprite12->Initialize(spriteCommon);
		sprite12->SetPozition(position12);
		sprite12->SetSize(XMFLOAT2{ 1280.0f,720.0f });

		sprite13->Initialize(spriteCommon);
		sprite13->SetPozition(position13);
		sprite13->SetSize(XMFLOAT2{ 1280.0f,720.0f });

		sprite14->Initialize(spriteCommon);
		sprite14->SetPozition(position14);
		sprite14->SetSize(XMFLOAT2{ 1280.0f,720.0f });

	}
	//�X�v���C�g�̉摜�w��
	{
		spriteCommon->LoadTexture(0, "eri.png");
		sprite->SetTextureIndex(0);
		spriteCommon->LoadTexture(1, "e.png");
		sprite1->SetTextureIndex(1);
		spriteCommon->LoadTexture(2, "ynkm.png");
		sprite2->SetTextureIndex(2);

		spriteCommon->LoadTexture(3, "hi.png");
		sprite3->SetTextureIndex(3);
		spriteCommon->LoadTexture(4, "hida.png");
		sprite4->SetTextureIndex(4);

		spriteCommon->LoadTexture(5, "mi.png");
		sprite5->SetTextureIndex(5);
		spriteCommon->LoadTexture(6, "migi.png");
		sprite6->SetTextureIndex(6);

		spriteCommon->LoadTexture(7, "konpas.png");
		sprite7->SetTextureIndex(7);

		spriteCommon->LoadTexture(8, "q.png");
		sprite8->SetTextureIndex(8);

		spriteCommon->LoadTexture(9, "spa.png");
		sprite9->SetTextureIndex(9);

		spriteCommon->LoadTexture(10, "sam.png");
		sprite10->SetTextureIndex(10);

		spriteCommon->LoadTexture(11, "sasa.png");
		sprite11->SetTextureIndex(11);

		spriteCommon->LoadTexture(12, "sh.png");
		sprite12->SetTextureIndex(12);

		spriteCommon->LoadTexture(13, "sh1.png");
		sprite13->SetTextureIndex(13);

		spriteCommon->LoadTexture(14, "sh2.png");
		sprite14->SetTextureIndex(14);

	}
	// OBJ���烂�f���f�[�^��ǂݍ���
	{
		model = Model::LoadFromOBJ("as");
		model2 = Model::LoadFromOBJ("as2");
		model3 = Model::LoadFromOBJ("yazi");
	}
	//3D�I�u�W�F�N�g����
	{
		object3d = Object3d::Create();
		object3d_2 = Object3d::Create();
		object3d_3 = Object3d::Create();
	}
	// �I�u�W�F�N�g�Ƀ��f����R�Â���
	{
		object3d->SetModel(model);
		object3d_2->SetModel(model2);
		object3d_3->SetModel(model3);
	}
	//3D�I�u�W�F�N�g�̈ʒu���w��
	{
		object3d_2->SetPosition({ -5,-5,0 });
		object3d_3->SetPosition({ 45,22,0 });
		object3d_3->SetScale({ 0.7,0.7,0.7 });
		object3d_3->SetRotation({ 0,0,0 });
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
	audio->LoadWave("bb.wav");
	isDrornFlag = 0;

	audio->LoadWave("one.wav");
	audio->LoadWave("her.wav");

	audio->LoadWave("nige.wav");
}


void GameScene::Update() {
	//�����Đ�
	if (soundCheckFlag[0] == 0) {
		//�����Đ�
		pSourceVoice[3] = audio->PlayWave("bb.wav");
		soundCheckFlag[0] = 1;
	}

	if (isDrornFlag == 0) {
		pSourceVoice[3]->SetVolume(0.4f);
	}
	else if (isDrornFlag == 1) {
		pSourceVoice[3]->SetVolume(0.1f);
	}

	if (input->TriggerKey(DIK_E)) {
		pSourceVoice[0] = audio->PlayWave("one.wav");
		pSourceVoice[0]->SetVolume(0.8f);
		pSourceVoice[1] = audio->PlayWave("her.wav");
		pSourceVoice[1]->SetVolume(0.5f);
		isDrornFlag = 1;
	}
	if (isDrornFlag == 1) {
		isChangeDrornTimer++;
	}
	if (isChangeDrornTimer > 80) {
		isChangeDrornTimer = 0;
		isDrornFlag = 0;
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
	object3d_3->Update();
	// �R���p�X�ړ�
	if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// ���݂̍��W���擾
		XMFLOAT3 rotate = object3d_3->GetRotation();

		// �ړ���̍��W���v�Z
		if (input->PushKey(DIK_RIGHT)) {
			rotate.z -= 1.0f;
		}
		else if (input->PushKey(DIK_LEFT)) { rotate.z += 1.0f; }

		// ���W�̕ύX�𔽉f
		object3d_3->SetRotation(rotate);
	}

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

	// �I�u�W�F�N�g�ړ�
	isLeftFlag = 0;
	if (input->PushKey(DIK_LEFT)) {
		isLeftFlag = 1;
	}

	isRightFlag = 0;
	if (input->PushKey(DIK_RIGHT)) {
		isRightFlag = 1;
	}

	// �p�[�e�B�N���N��(������)
	if (input->TriggerKey(DIK_P)) {

		//�p�[�e�B�N���͈�
		for (int i = 0; i < 50; i++) {
			//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
			const float rnd_pos = 0.03f;
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
			const float rnd_acc = -0.01f;
			const float rnd_acc_v = -0.01f;
			XMFLOAT3 acc{};
			acc.x = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
			acc.y = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
			//acc.z = (float)rand() / RAND_MAX * rnd_acc;

			//�ǉ�
			particleManager->Add(10, pos, vel, acc, 1.0f, 0.0f);
		}
	}
	particleManager->Update();
	fbxObject3d_->Update();
	fbxObject3d_2->Update();

	//�u���b�N�A�E�g
	if (input->TriggerKey(DIK_C)) {
		if (isSHFlag == 0) {
			isSHFlag = 1;
		}
	}
	if (isSHFlag == 1) {
		SHtimer++;
	}
	if (SHtimer >= 10) {
		SHtimer = 0;
		isSHFlag = 0;
	}

}

void GameScene::Draw() {
	/*sprite->Draw();
	sprite2->Draw();*/

	sprite1->Draw();

	if (isLeftFlag == 0) {
		sprite3->Draw();
	}
	else if (isLeftFlag == 1) {
		sprite4->Draw();
	}

	if (isRightFlag == 0) {
		sprite5->Draw();
	}
	else if (isRightFlag == 1) {
		sprite6->Draw();
	}
	sprite7->Draw();

	sprite8->Draw();

	sprite9->Draw();

	sprite10->Draw();

	if (input->PushKey(DIK_SPACE)) {
		sprite11->Draw();
	}

	if (SHtimer >= 1 && SHtimer <= 4) {
		sprite14->Draw();
	}
	else if (SHtimer >= 5 && SHtimer <= 7) {
		sprite13->Draw();
	}
	else if (SHtimer >= 8 && SHtimer <= 10) {
		sprite12->Draw();
	}

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>

	//3D�I�u�W�F�N�g�̕`��
	object3d->Draw();
	object3d_2->Draw();
	object3d_3->Draw();

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