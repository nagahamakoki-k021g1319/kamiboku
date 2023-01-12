#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dオブジェクト解放
	delete object3d;
	delete object3d_2;

	//3Dモデル解放
	delete model;
	delete model2;

	//オーディオ解放
	audio->Finalize();
	delete audio;

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	//スプライトの初期化
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
	//スプライトの画像指定
	{
		spriteCommon->LoadTexture(0, "eri.png");
		sprite->SetTextureIndex(0);
		spriteCommon->LoadTexture(1, "feri.png");
		sprite1->SetTextureIndex(1);
		spriteCommon->LoadTexture(2, "ynkm.png");
		sprite2->SetTextureIndex(2);
	}
	// OBJからモデルデータを読み込み
	{
		model = Model::LoadFromOBJ("as");
		model2 = Model::LoadFromOBJ("as2");
	}
	//3Dオブジェクト生成
	{
		object3d = Object3d::Create();
		object3d_2 = Object3d::Create();
	}
	// オブジェクトにモデルを紐づける
	{
		object3d->SetModel(model);
		object3d_2->SetModel(model2);
	}
	//3Dオブジェクトの位置を指定
	{
		object3d_2->SetPosition({ -5,-5,0 });
	}


	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("cr.wav");
	audio->LoadWave("tit.wav");

	
}


void GameScene::Update() {
	object3d->Update();
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		XMFLOAT3 position = object3d->GetPosition();

		// 移動後の座標を計算
		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		// 座標の変更を反映
		object3d->SetPosition(position);
	}

	object3d_2->Update();

	//当たり判定
	XMFLOAT3 a = object3d_2->GetPosition();
	XMFLOAT3 b = object3d->GetPosition();
	float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
	float lenR = std::pow(1.0f + 1.0f, 2.0f);
	if (xyz <= lenR) {
		ischackFlag = 1;
	}
	// リセット
	if (input->PushKey(DIK_R)) {
		ischackFlag = 0;
	}


	//音声再生
	if (soundCheckFlag == 0) {
		//音声再生
		audio->PlayWave("tit.wav");
		soundCheckFlag = 1;
	}
	if (input->TriggerKey(DIK_SPACE)) {
		//音声再生
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

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>

	//3Dオブジェクトの描画
	object3d->Draw();
	object3d_2->Draw();


	//3Dオブジェクト描画後処理
	Object3d::PostDraw();


}