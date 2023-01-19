#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	//3Dオブジェクト解放
	delete homeOBJ;
	delete player;
	delete reticle;
	delete zango;
	for (int i = 1; i < 5; i++) {
		delete PopPos_[i];
	}

	//3Dモデル解放
	delete model;
	delete model2;
	delete reticleMD;
	delete zangoMD;
	delete eneMD;

	//オーディオ解放
	audio->Finalize();
	delete audio;

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(gamescene);


	gamescene_ = gamescene;
	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);
	//ビューの生成
	{
		view = new View();
	}
	//ビューの初期化
	{
		view->Initialize();
	}

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
		reticleMD = Model::LoadFromOBJ("cube");
		zangoMD = Model::LoadFromOBJ("zango");
		eneMD = Model::LoadFromOBJ("ene");
	}
	//3Dオブジェクト生成
	{
		homeOBJ = Object3d::Create();
		player = Object3d::Create();
		reticle = Object3d::Create();
		zango = Object3d::Create();
		for (int i = 0; i < 5; i++) {
			PopPos_[i] = Object3d::Create();
		}
	}
	// 親子設定
	{
		player->SetParent(homeOBJ);
		for (int i = 1; i < 5; i++) {
			PopPos_[i]->SetParent(PopPos_[0]);
		}
	}
	// オブジェクトにモデルを紐づける
	{
		homeOBJ->SetModel(model);
		player->SetModel(model2);
		reticle->SetModel(reticleMD);
		zango->SetModel(zangoMD);
		for (int i = 0; i < 5; i++) {
			PopPos_[i]->SetModel(reticleMD);
		}
	}
	//3Dオブジェクトの位置を指定
	{
		player->wtf.position = Vector3{ 0,1,15 };
		homeOBJ->wtf.position = Vector3{ 0,1,0 };

		PopPos_[1]->wtf.position = Vector3{ 0,0,150 };
		PopPos_[2]->wtf.position = Vector3{ 0,0,-150 };
		PopPos_[3]->wtf.position = Vector3{ 150,0,0 };
		PopPos_[4]->wtf.position = Vector3{ -150,0,0 };
	}
	{
		homeOBJ->wtf.scale = Vector3{ 3,3,3 };
		zango->wtf.scale = (Vector3{ 5, 3.5f, 5 });
	}


	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("cr.wav");
	audio->LoadWave("mm.wav");


}


void GameScene::Update() {
	srand((unsigned)time(nullptr));
	int popRand = rand() % 4 + 1;

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		Vector3 rotate = homeOBJ->wtf.rotation;

		// 移動後の座標を計算
		/*if (input->PushKey(DIK_UP)) { rotate.x += 0.5f; }
		else if (input->PushKey(DIK_DOWN)) { rotate.x -= 0.5f; }*/
		if (input->PushKey(DIK_RIGHT)) { rotate.y += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { rotate.y -= 1.0f; }

		// 座標の変更を反映

		homeOBJ->wtf.rotation = rotate;
	}
	homeOBJ->Update(view);
	player->Update(view);
	zango->Update(view);
	//敵ポップ
	for (int i = 0; i < _countof(enemys); i++) {

		enemys[i].Update(eneMD, Affin::GetWorldTrans(homeOBJ->wtf.matWorld), view);

	}
	for (int i = 0; i < 5; i++) {
		PopPos_[i]->Update(view);
	}
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->Update(resultRet, view);
	}
	//敵更新
	for (std::unique_ptr<EnemyBullet>& Ebullet : eneBullets_) {
		Ebullet->Update(view);
	}

	{
		Reticle3D();
		if (input->PushKey(DIK_Q)) {
			zango->wtf.position.y = -1;
			if (input->PushKey(DIK_SPACE))
			{
				Attack();
			}
		}
		else {
			zango->wtf.position.y = 2;
		}
	}


	{
		//デスフラグの立った弾を削除
		bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) { return bullet->IsDead(); });
		//デスフラグの立った弾を削除
		eneBullets_.remove_if(
			[](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });

		//敵ポップ
		for (int i = 0; i < _countof(enemys); i++) {
			enemys[i].SetGameScene(gamescene_);
		}

		if (waitTimer == 0) {
			if (popCount > 0) {
				if (popTime == 0) {
					for (int i = 0; i < _countof(enemys); i++) {
						if (enemys[i].isDead == true) {
							enemys[i].Pop(Affin::GetWorldTrans(PopPos_[popRand]->wtf.matWorld), popRand, eneMD);

							break;
						}
					}
					popCount--;
					popTime = 150;
				}
				else {
					popTime--;
				}
			}
			else {
				if (wave == 0) {
					wave = 1;
				}
			}
		}
		else {
			waitTimer--;
		}
		CheckAlive(enemys);
		//ウェーブ&勝利判定
		if (wave >= 0 && popCount == 0) {
			if (CheckAlive(enemys) == true) {
				if (wave < 3) {
					wave++;
					if (wave == 3) {
						popCount = 30;
					}
					else if (wave == 2) {
						popCount = 20;
					}
					else if (wave == 1) {
						popCount = 10;
					}
					waitTimer = 250;
				}
				else if (wave == 3) {
					//scene = 2;
				}
			}
		}

	}



	//当たり判定
	{
		Vector3 a = player->wtf.position;
		Vector3 b = homeOBJ->wtf.position;
		float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
		float lenR = std::pow(1.0f + 1.0f, 2.0f);
		if (xyz <= lenR) {
			ischackFlag = 1;
		}
	}
	//当たり判定
	{
		Vector3 a = player->wtf.position;
		Vector3 b = homeOBJ->wtf.position;
		float xyz = std::pow(a.x - b.x, 2.0f) + std::pow(a.y - b.y, 2.0f) + std::pow(a.z - b.z, 2.0f);
		float lenR = std::pow(1.0f + 1.0f, 2.0f);
		if (xyz <= lenR) {
			ischackFlag = 1;
		}
	}
	//当たり判定 pBullet->enemy
	{
		//判定対象aとbの座標
		Vector3 posA, posB;

		//自機弾リストの取得
		const std::list<std::unique_ptr<Bullet>>& playerBullet = bullets_;
		//敵の弾リストの取得
		const std::list<std::unique_ptr<EnemyBullet>>& enemyBullet = eneBullets_;

#pragma region 自キャラと敵弾の当たり判定
		for (const std::unique_ptr<Bullet>& bullet : bullets_) {
			posA = bullet.get()->GetWorldPosition();

			//自弾と敵弾
			for (const std::unique_ptr<EnemyBullet>& enebullet : enemyBullet) {
				posB = bullet.get()->GetWorldPosition();

				float x = posA.x - posB.x;
				float y = posA.y - posB.y;
				float z = posA.z - posB.z;

				float distance = sqrt(x * x + y * y + z * z);

				Matrix4 matA = bullet->obj3d.wtf.matWorld;
				Matrix4 matB = enebullet->obj3d.wtf.matWorld;

				//弾と弾の交差判定
				if (distance < matA.m[0][0] + matB.m[0][0]) {	//スケールxを半径として使用
					/*player_->OnCollision();*/
					//enebullet->OnColision();
				}

			}
		}
#pragma endregion


#pragma region 自弾と敵キャラの当たり判定
		for (int i = 0; i < _countof(enemys); i++) {


			//自キャラ座標
			posA = enemys[i].GetWorldPosition();

			//自キャラと敵弾
			for (const std::unique_ptr<Bullet>& bullet : bullets_) {
				posB = bullet.get()->GetWorldPosition();

				float x = posA.x - posB.x;
				float y = posA.y - posB.y;
				float z = posA.z - posB.z;

				float distance = sqrt(x * x + y * y + z * z);

				Matrix4 matA = enemys[i].obj3d.wtf.matWorld;
				Matrix4 matB = bullet->obj3d.wtf.matWorld;

				//弾と弾の交差判定
				if (distance <= matA.m[0][0] + matB.m[0][0]) {	//スケールxを半径として使用
					enemys[i].OnColision();
					bullet->OnColision();
				}

			}
		}
#pragma endregion
	}

	// カメラのプログラム持ってきただけ
	{
		//// カメラ移動更新処理
		// スタート地点	：start
		// エンド地点		：end
		// 経過時間		：elapsedTime [s]
		// 移動完了の率（経過時間/全体時間） ：timeRate (%)
		nowCount++;

		if (input->TriggerKey(DIK_R)) {
			startCount = nowCount;
			switch (cameraState)
			{
			case 0:
				cameraState = 1;
				break;
			case 2:
				cameraState = 3;
				break;
			}
		}

		elapsedCount = nowCount - startCount;
		elapsedTime = static_cast<float> (elapsedCount) / 1.0f;
		timeRate = min(elapsedTime / maxTime, 1.0f);

		if (cameraState == 1) {
			Vector3 A, B, C, AB, AC, FL, FLst, FLen;
			p0 = Affin::GetWorldTrans(player->wtf.matWorld);
			p1 = Vector3(0, 0, 0);
			p2 = Vector3(0, 150, 0);
			p3 = Vector3(0, 150, 1);
			A = Vector3::lerp(p0, p1, timeRate);
			B = Vector3::lerp(p1, p2, timeRate);
			C = Vector3::lerp(p1, p3, timeRate);
			AB = Vector3::lerp(A, B, timeRate);
			AC = Vector3::lerp(A, C, timeRate - 0.1);
			FLst = Vector3(90, 0, 0);
			FLen = Vector3(20, 0, 1);
			FL = Vector3::lerp(FLst, FLen, timeRate - 0.1);
			view->focalLengs = FL.x;

			view->eye = AB;
			view->target = AC;
			if (timeRate >= 1.0) {
				cameraState = 2;
			}
		}
		if (cameraState == 3) {
			Vector3 A, B, C, AB, AC, FL, FLst, FLen;
			p0 = Vector3(0, 150, 0);
			p1 = Vector3(0, 0, 0);
			p2 = Affin::GetWorldTrans(player->wtf.matWorld);
			p3 = Affin::GetWorldTrans(reticle->wtf.matWorld);
			A = Vector3::lerp(p0, p1, timeRate);
			B = Vector3::lerp(p1, p2, timeRate);
			C = Vector3::lerp(p1, p3, timeRate);
			AB = Vector3::lerp(A, B, timeRate - 0.01);
			AC = Vector3::lerp(A, C, timeRate);
			FLst = Vector3(20, 0, 0);
			FLen = Vector3(90, 0, 1);
			FL = Vector3::lerp(FLst, FLen, timeRate - 0.1);
			view->focalLengs = FL.x;

			view->eye = AB;
			view->target = AC;
			if (timeRate >= 1.0) {
				cameraState = 0;
			}
		}




		if (cameraState == 0) {
			ai = Affin::GetWorldTrans(player->wtf.matWorld);
			view->focalLengs = 90;

			view->eye = { ai.x,ai.y,ai.z };
			view->target = Affin::GetWorldTrans(reticle->wtf.matWorld);
		}
		else if (cameraState == 2) {
			view->focalLengs = 20;

			view->eye = Vector3(0, 150, 0);
			view->target = Affin::GetWorldTrans(player->wtf.matWorld);

		}
	}


	// リセット
	if (input->PushKey(DIK_R)) {
		ischackFlag = 0;
	}
	//音声再生
	if (input->TriggerKey(DIK_O)) {
		//音声再生
		audio->PlayWave("mm.wav");
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
	homeOBJ->Draw();
	player->Draw();
	reticle->Draw();
	zango->Draw();
	for (int i = 0; i < _countof(enemys); i++) {
		if (enemys[i].isDead == false) {
			enemys[i].obj3d.Draw();
		}
	}
	for (int i = 1; i < _countof(PopPos_); i++) {
		PopPos_[i]->Draw();
	}
	//弾描画
	for (std::unique_ptr<Bullet>& bullet : bullets_) {
		bullet->obj3d.Draw();
	}
	//弾描画
	for (std::unique_ptr<EnemyBullet>& Ebullet : eneBullets_) {
		Ebullet->obj3d.Draw();
	}


	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

}

void GameScene::Reticle3D() {
	//自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = { 0.0f, 0, -1.0f };
	//自機のワールド行列の回転を反映
	offset = Affin::VecMat(offset, player->wtf.matWorld);
	//ベクトルの長さを整える
	//offset.nomalize();
	float len = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
	if (len != 0) {
		offset /= len;
	}
	offset *= -100;
	reticle->wtf.position = offset;
	reticle->wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	reticle->wtf.matWorld = Affin::matScale(reticle->wtf.scale);
	reticle->wtf.matWorld = Affin::matTrans(reticle->wtf.position);

	reticle->Update(view);

}

void GameScene::Attack()
{
	if (coolTime <= 0) {
		//弾を生成し、初期化
		std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();

		pos = Affin::GetWorldTrans(player->wtf.matWorld);
		pos.y = 0;
		ret3DPos = Affin::GetWorldTrans(reticle->wtf.matWorld);
		velo = ret3DPos - pos;
		velo.nomalize();
		resultRet = velo * newBullet->speed;
		resultRet.nomalize();
		newBullet->Initialize(reticleMD, pos, resultRet);

		//弾を登録
		bullets_.push_back(std::move(newBullet));

		//クールタイムをリセット
		coolTime = 25;
	}
	else {
		coolTime--;
	}

}

int GameScene::CheckAlive(Enemy enemys_[]) {
	aliveNum = 0;

	for (int i = 0; i < _countof(enemys); i++) {
		if (enemys[i].isDead == false) {
			aliveNum++;
		}
	}

	if (aliveNum == 0) {
		return true;
	}
	else {
		return false;
	}
}