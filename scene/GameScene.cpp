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
	delete floor;

	//FBXオブジェクト解放
	delete fbxObject3d_;
	delete fbxModel_;

	delete fbxObject3d_2;
	delete fbxModel2_;

	//オーディオ解放
	audio->Finalize();
	delete audio;

	delete particleManager;

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

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	FBXObject3d::SetCamera(camera);

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
		sprite1->SetSize(XMFLOAT2{ WinApp::window_width,WinApp::window_height });

		sprite2->Initialize(spriteCommon);
		position2.x = 900.0f;
		sprite2->SetPozition(position2);
		sprite2->SetSize(XMFLOAT2{ 300.0f,170.0f });

		titleSP->Initialize(spriteCommon);
		titleSP->SetPozition(titlePOS);
		titleSP->SetSize(XMFLOAT2{ WinApp::window_width,WinApp::window_height });
		endSP->Initialize(spriteCommon);
		endSP->SetPozition(endPOS);
		endSP->SetSize(XMFLOAT2{ WinApp::window_width,WinApp::window_height });

		retSP->Initialize(spriteCommon);
		retPOS = XMFLOAT2{ (WinApp::window_width - 100) / 2,(WinApp::window_height - 100) / 2 };
		retSP->SetPozition(retPOS);
		//retSP->SetSize(XMFLOAT2{ WinApp::window_width / 5,WinApp::window_height / 10 });

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
		position8.x = 83.0f;
		position8.y = 560.0f;
		sprite8->SetPozition(position8);
		sprite8->SetSize(XMFLOAT2{ 35.0f,50.0f });

		sprite9->Initialize(spriteCommon);
		position9.x = 83.0f;
		position9.y = 560.0f;
		sprite9->SetPozition(position9);
		sprite9->SetSize(XMFLOAT2{ 35.0f,50.0f });

		sprite10->Initialize(spriteCommon);
		position10.x = 25.0f;
		position10.y = 25.0f;
		sprite10->SetPozition(position10);
		sprite10->SetSize(XMFLOAT2{ 150.0f,115.0f });

		sprite12->Initialize(spriteCommon);
		sprite12->SetPozition(position12);
		sprite12->SetSize(XMFLOAT2{ 1280.0f,720.0f });

		sprite13->Initialize(spriteCommon);
		sprite13->SetPozition(position13);
		sprite13->SetSize(XMFLOAT2{ 1280.0f,720.0f });

		sprite14->Initialize(spriteCommon);
		sprite14->SetPozition(position14);
		sprite14->SetSize(XMFLOAT2{ 1280.0f,720.0f });

		sprite15->Initialize(spriteCommon);
		position15.x = 1200.0f;
		position15.y = 80.0f;
		sprite15->SetPozition(position15);
		sprite15->SetSize(XMFLOAT2{ 30.0f,30.0f });

		sprite16->Initialize(spriteCommon);
		position16.x = 25.0f;
		position16.y = 25.0f;
		sprite16->SetPozition(position16);
		sprite16->SetSize(XMFLOAT2{ 150.0f,115.0f });

	}
	//スプライトの画像指定
	{
		spriteCommon->LoadTexture(0, "eri.png");
		sprite->SetTextureIndex(0);
		spriteCommon->LoadTexture(1, "info.png");
		sprite1->SetTextureIndex(1);
		spriteCommon->LoadTexture(2, "ynkm.png");
		sprite2->SetTextureIndex(2);
		spriteCommon->LoadTexture(3, "Title.png");
		titleSP->SetTextureIndex(3);
		spriteCommon->LoadTexture(4, "end.png");
		endSP->SetTextureIndex(4);
		spriteCommon->LoadTexture(5, "2Dret.png");
		retSP->SetTextureIndex(5);
		spriteCommon->LoadTexture(6, "hi.png");
		sprite3->SetTextureIndex(6);
		spriteCommon->LoadTexture(7, "hida.png");
		sprite4->SetTextureIndex(7);
		spriteCommon->LoadTexture(8, "mi.png");
		sprite5->SetTextureIndex(8);
		spriteCommon->LoadTexture(9, "migi.png");
		sprite6->SetTextureIndex(9);
		spriteCommon->LoadTexture(12, "konpas.png");
		sprite7->SetTextureIndex(12);
		spriteCommon->LoadTexture(10, "u.png");
		sprite8->SetTextureIndex(10);
		spriteCommon->LoadTexture(11, "ue.png");
		sprite9->SetTextureIndex(11);
		spriteCommon->LoadTexture(13, "e1.png");
		sprite10->SetTextureIndex(13);
		spriteCommon->LoadTexture(14, "sh.png");
		sprite12->SetTextureIndex(14);
		spriteCommon->LoadTexture(15, "sh1.png");
		sprite13->SetTextureIndex(15);
		spriteCommon->LoadTexture(16, "sh2.png");
		sprite14->SetTextureIndex(16);
		spriteCommon->LoadTexture(17, "yazi1.png");
		sprite15->SetTextureIndex(17);
		spriteCommon->LoadTexture(18, "e2.png");
		sprite16->SetTextureIndex(18);
	}
	// OBJからモデルデータを読み込み
	{
		model = Model::LoadFromOBJ("as");
		model2 = Model::LoadFromOBJ("as2");
		reticleMD = Model::LoadFromOBJ("cube");
		zangoMD = Model::LoadFromOBJ("zango");
		eneMD = Model::LoadFromOBJ("ene");
		floorMD = Model::LoadFromOBJ("floor");
		skydomeMD = Model::LoadFromOBJ("skydome");


	}
	//3Dオブジェクト生成
	{
		homeOBJ = Object3d::Create();
		player = Object3d::Create();
		reticle = Object3d::Create();
		zango = Object3d::Create();
		floor = Object3d::Create();
		skydome = Object3d::Create();
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
		floor->SetModel(floorMD);
		skydome->SetModel(skydomeMD);
		for (int i = 0; i < 5; i++) {
			PopPos_[i]->SetModel(reticleMD);
		}

	}
	//3Dオブジェクトの位置を指定
	{
		player->wtf.position = Vector3{ 0,1,15 };
		homeOBJ->wtf.position = Vector3{ 0,1,0 };
		floor->wtf.position = Vector3{ 0,-1,0 };

		PopPos_[1]->wtf.position = Vector3{ 0,0,150 };
		PopPos_[2]->wtf.position = Vector3{ 0,0,-150 };
		PopPos_[3]->wtf.position = Vector3{ 150,0,0 };
		PopPos_[4]->wtf.position = Vector3{ -150,0,0 };
	}
	{
		homeOBJ->wtf.scale = Vector3{ 3,3,3 };
		zango->wtf.scale = (Vector3{ 45, 4, 45 });
		skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	}
	//3Dオブジェクトを一回アップデート
	{

		if (cameraState == 0) {
			ai = Vector3{ 0,1,45 };
			view->focalLengs = 90;

			view->eye = { ai.x,ai.y,ai.z };
			view->target = Vector3{ 0,1,80 };
		}

		homeOBJ->Update(view);
		player->Update(view);
		zango->Update(view);
		floor->Update(view);
		skydome->Update(view);
		for (int i = 0; i < 5; i++) {
			PopPos_[i]->Update(view);
		}

	}

	fbxModel_ = FbxLoader::GetInstance()->LoadModelFromFile("Player");
	fbxModel2_ = FbxLoader::GetInstance()->LoadModelFromFile("Player");

	// デバイスをセット
	FBXObject3d::SetDevice(dxCommon->GetDevice());
	// グラフィックスパイプライン生成
	FBXObject3d::CreateGraphicsPipeline();


	fbxObject3d_ = new FBXObject3d;
	fbxObject3d_->Initialize();
	fbxObject3d_->SetModel(fbxModel_);
	fbxObject3d_->SetScale({ 0.01,0.01,0.01 });
	fbxObject3d_->SetPosition({ 0,10,40 });
	fbxObject3d_->PlayAnimation();

	fbxObject3d_2 = new FBXObject3d;
	fbxObject3d_2->Initialize();
	fbxObject3d_2->SetModel(fbxModel2_);
	fbxObject3d_2->SetScale({ 0.01,0.01,0.01 });
	fbxObject3d_2->SetPosition({ -10,10,40 });
	fbxObject3d_2->PlayAnimation();


	// パーティクル生成
	particleManager = ParticleManager::Create();
	particleManager->Update();

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("gate.wav");
	audio->LoadWave("tt.wav");
	audio->LoadWave("bb.wav");

	isDrornFlag = 0;
	audio->LoadWave("one.wav");
	audio->LoadWave("her.wav");
	audio->LoadWave("oka.wav");

}


void GameScene::Update() {
	srand((unsigned)time(nullptr));
	int popRand = rand() % 4 + 1;

	switch (scene)
	{
	case 0:// title
		//音声再生
		if (soundCheckFlag == 0) {
			//音声再生
			pSourceVoice[0] = audio->PlayWave("tt.wav");
			soundCheckFlag = 1;
		}
		if (input->TriggerKey(DIK_SPACE)) {
			scene = 1;
		}

		// 自弾
		burstBL = 0;
		burstCoolTime = 0;
		// カメラ関係
		startCount = 0;
		nowCount = 0;
		elapsedCount = 0;
		elapsedTime = 0;
		maxTime = 50.0f;
		timeRate = 0;
		maxTimeRate = 0;
		cameraState = 2;
		// 敵
		popTime = 0;
		coolTime = 0;
		killCounter;
		popCount = 0;
		wave = 0;
		waitTimer = 250;

		HP = 10;

		rotatte = -135;

		break;

	case 3: // end
		pSourceVoice[1]->Stop();
		if (input->TriggerKey(DIK_SPACE)) {
			scene = 0;
		}
		for (int i = 0; i < _countof(enemys); i++) {
			enemys[i].OnColision();
		}
		for (std::unique_ptr<EnemyBullet>& Ebullet : eneBullets_) {
			Ebullet->OnColision();
		}
		soundCheckFlag = 0;
		soundCheckFlag2 = 0;
		break;

	case 1:// info()	

		// カメラのプログラム持ってきただけ
	{
		//// カメラ移動更新処理
		// スタート地点	：start
		// エンド地点		：end
		// 経過時間		：elapsedTime [s]
		// 移動完了の率（経過時間/全体時間） ：timeRate (%)
		nowCount++;

		if (input->TriggerKey(DIK_E)) {
			pSourceVoice[0]->Stop();
			if (soundCheckFlag2 == 0) {
				//音声再生
				pSourceVoice[1] = audio->PlayWave("bb.wav");
				soundCheckFlag2 = 1;
			}

			startCount = nowCount;
			switch (cameraState)
			{
			case 0:
				cameraState = 1;
				break;
			case 2:
				scene = 2;
				// カメラ関係
				startCount = 0;
				nowCount = 0;
				elapsedCount = 0;
				elapsedTime = 0;
				maxTime = 50.0f;
				timeRate;
				maxTimeRate;
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
	homeOBJ->Update(view);
	player->Update(view);
	zango->Update(view);
	floor->Update(view);
	skydome->Update(view);
	for (int i = 0; i < 5; i++) {
		PopPos_[i]->Update(view);
	}

	break;
	case 2: // game
		isDireFlag = 0;
		isHit = 0;

		// オブジェクト移動
		if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
		{
			// 現在の座標を取得
			Vector3 rotate = homeOBJ->wtf.rotation;

			// 移動後の座標を計算
			/*if (input->PushKey(DIK_UP)) { rotate.x += 0.5f; }
			else if (input->PushKey(DIK_DOWN)) { rotate.x -= 0.5f; }*/

			if (input->PushKey(DIK_D)) {
				isDireFlag = 2;
				rotate.y += 1.0f;
			}
			if (input->PushKey(DIK_A)) {
				isDireFlag = 1;
				rotate.y -= 1.0f;
			}


			// 座標の変更を反映

			homeOBJ->wtf.rotation = rotate;
		}
		isLeftFlag = 0;
		if (input->PushKey(DIK_A)) {
			isLeftFlag = 1;
			rotatte += -1.0f;
		}
		isRightFlag = 0;
		if (input->PushKey(DIK_D)) {
			isRightFlag = 1;
			rotatte += 1.0f;
		}
		isUpFlag = 0;
		if (input->PushKey(DIK_W)) {
			isUpFlag = 1;
		}

		sprite15->SetRotation(rotatte);

		homeOBJ->Update(view);
		player->Update(view);
		zango->Update(view);
		floor->Update(view);
		skydome->Update(view);

		//敵ポップ
		for (int i = 0; i < _countof(enemys); i++) {
			enemys[i].Update(eneMD, Affin::GetWorldTrans(player->wtf.matWorld), view);
		}
		for (int i = 0; i < 5; i++) {
			PopPos_[i]->Update(view);
		}
		for (std::unique_ptr<Bullet>& bullet : bullets_) {
			bullet->Update(view);
		}
		//敵更新
		for (std::unique_ptr<EnemyBullet>& Ebullet : eneBullets_) {
			Ebullet->Update(view);
		}

		fbxObject3d_->Update();
		fbxObject3d_2->Update();


		{
			Reticle3D();
			if (burstCoolTime < 0) {
				if (cameraState == 0 || cameraState == 1) {
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
			}
			else {
				burstCoolTime--;
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
		//当たり判定 eBullet->player
		{
			if (input->PushKey(DIK_Q) && cameraState == 0 || cameraState == 1) {
				//判定対象aとbの座標
				Vector3 posA, posB;

				//敵の弾リストの取得
				const std::list<std::unique_ptr<EnemyBullet>>& enemyBullet = eneBullets_;

				posA = Affin::GetWorldTrans(player->wtf.matWorld);

				//自弾と敵弾
				for (const std::unique_ptr<EnemyBullet>& enebullet : enemyBullet) {
					posB = enebullet.get()->GetWorldPosition();

					float x = posA.x - posB.x;
					float y = posA.y - posB.y;
					float z = posA.z - posB.z;

					float distance = sqrt(x * x + z * z);// Yの計算抜いた

					Matrix4 matA = player->wtf.matWorld;
					Matrix4 matB = enebullet->obj3d.wtf.matWorld;

					//弾と弾の交差判定
					if (distance < 3 + matB.m[0][0]) {	//スケールxを半径として使用
						isHit = 1;
						enebullet->OnColision();
					}

				}
			}
			if (isHit == 1) {
				HP--;


				//パーティクル範囲
				for (int i = 0; i < 50; i++) {
					//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
					const float rnd_pos = 3.03f;
					//const float rnd_posX = 1.0f;
					XMFLOAT3 pos{};
					pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
					pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
					pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

					//速度
					//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
					const float rnd_vel = 0.5f;
					XMFLOAT3 vel{};
					vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
					vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
					vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
					//重力に見立ててYのみ[-0.001f,0]でランダムに分布
					const float rnd_acc = -0.01f;
					const float rnd_acc_v = -0.01f;
					XMFLOAT3 acc{};
					acc.x = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
					acc.y = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
					//acc.z = (float)rand() / RAND_MAX * rnd_acc;

					//追加
					particleManager->Add(10, pos, vel, acc, 1.0f, 0.0f);

				}
			}
			if (HP < 0) {
				scene = 3;
			}
		}
		//当たり判定 eBullet->zango
		{
			if (!input->PushKey(DIK_Q) || cameraState == 2 || cameraState == 3) {


				//判定対象aとbの座標
				Vector3 posA, posB;
				//敵の弾リストの取得
				const std::list<std::unique_ptr<EnemyBullet>>& enemyBullet = eneBullets_;
				posA = Affin::GetWorldTrans(homeOBJ->wtf.matWorld);

				//自弾と敵弾
				for (const std::unique_ptr<EnemyBullet>& enebullet : enemyBullet) {
					posB = enebullet.get()->GetWorldPosition();

					float x = posA.x - posB.x;
					float y = posA.y - posB.y;
					float z = posA.z - posB.z;

					float distance = sqrt(x * x + y * y + z * z);

					Matrix4 matA = homeOBJ->wtf.matWorld;
					Matrix4 matB = enebullet->obj3d.wtf.matWorld;

					//弾と弾の交差判定
					if (distance < 70 + matB.m[0][0]) {	//スケールxを半径として使用
						enebullet->OnColision();
					}

				}
			}
		}

		// カメラのプログラム持ってきただけ
		{
			//// カメラ移動更新処理
			// スタート地点	：start
			// エンド地点		：end
			// 経過時間		：elapsedTime [s]
			// 移動完了の率（経過時間/全体時間） ：timeRate (%)
			nowCount++;

			if (input->TriggerKey(DIK_E)) {
				startCount = nowCount;
				switch (cameraState)
				{
				case 0:
					cameraState = 1;
					break;
				case 2:

					if (isSHFlag == 0) {
						isSHFlag = 1;
					}

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

		if (input->TriggerKey(DIK_E)) {
			if (isDrornFlag == 0) {
				pSourceVoice[0] = audio->PlayWave("one.wav");
				pSourceVoice[0]->SetVolume(0.8f);
				pSourceVoice[1] = audio->PlayWave("her.wav");
				pSourceVoice[1]->SetVolume(0.5f);
				isDrornFlag = 1;
			}
			else if (isDrornFlag == 1) {
				pSourceVoice[2] = audio->PlayWave("oka.wav");
				pSourceVoice[2]->SetVolume(0.8f);
				pSourceVoice[1] = audio->PlayWave("her.wav");
				pSourceVoice[1]->SetVolume(0.5f);
				isDrornFlag = 2;
			}

		}
		if (isDrornFlag == 1) {
			isChangeDrornTimer++;
		}
		else if (isDrornFlag == 2) {
			isChangeDrornTimer2++;
		}

		if (isChangeDrornTimer > 80) {
			isChangeDrornTimer = 0;
			isDrornFlag = 1;
		}
		else if (isChangeDrornTimer2 > 80) {
			isChangeDrornTimer2 = 0;
			isDrornFlag = 0;
		}

		//ブラックアウト
		if (isSHFlag == 1) {
			SHtimer++;
		}
		if (SHtimer >= 10) {
			SHtimer = 0;
			isSHFlag = 0;
		}



		// パーティクル起動(長押し)
		if (input->TriggerKey(DIK_P)) {

			//パーティクル範囲
			for (int i = 0; i < 50; i++) {
				//X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
				const float rnd_pos = 0.03f;
				//const float rnd_posX = 1.0f;
				XMFLOAT3 pos{};
				pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

				//速度
				//X,Y,Z全て[-0.05f,+0.05f]でランダムに分布
				const float rnd_vel = 0.5f;
				XMFLOAT3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//重力に見立ててYのみ[-0.001f,0]でランダムに分布
				const float rnd_acc = -0.01f;
				const float rnd_acc_v = -0.01f;
				XMFLOAT3 acc{};
				acc.x = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				acc.y = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				//acc.z = (float)rand() / RAND_MAX * rnd_acc;

				//追加
				particleManager->Add(10, pos, vel, acc, 1.0f, 0.0f);
			}
		}
		particleManager->Update();

		break;
	}
}

void GameScene::Draw() {


	switch (scene)
	{
	case 0:// title
		titleSP->Draw();
		break;
	case 3:// end
		endSP->Draw();
		break;
	case 1:// 
		//3Dオブジェクト描画前処理
		Object3d::PreDraw(dxCommon->GetCommandList());
		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// <summary>

		//3Dオブジェクトの描画
		//homeOBJ->Draw();
		player->Draw();



		//reticle->Draw();
		zango->Draw();
		floor->Draw();
		skydome->Draw();
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


		sprite1->Draw();
		break;
	case 2: // game
		sprite2->Draw();


		//3Dオブジェクト描画前処理
		Object3d::PreDraw(dxCommon->GetCommandList());
		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加できる
		/// <summary>

		//3Dオブジェクトの描画
		//homeOBJ->Draw();
		player->Draw();

		//reticle->Draw();
		zango->Draw();

		floor->Draw();
		skydome->Draw();

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







		//object3d_3->Draw();
		//3Dオブジェクト描画後処理
		Object3d::PostDraw();

		sprite7->Draw();
		sprite15->Draw();
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
		if (isUpFlag == 0) {
			sprite8->Draw();
		}
		else if (isUpFlag == 1) {
			sprite9->Draw();
		}
		
		if (cameraState == 0) {
			sprite10->Draw();
		}
		else if (cameraState == 2) {
			sprite16->Draw();
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

		fbxObject3d_->Draw(dxCommon->GetCommandList());
		fbxObject3d_2->Draw(dxCommon->GetCommandList());

		// 3Dオブジェクト描画前処理
		ParticleManager::PreDraw(dxCommon->GetCommandList());

		// 3Dオブクジェクトの描画
		particleManager->Draw();

		// 3Dオブジェクト描画後処理
		ParticleManager::PostDraw();

		// 前景スプライト
		if (input->ReleaseKey(DIK_Y)) {

			sprite->Draw();
		}
		if (input->PushKey(DIK_Q) && cameraState == 0 || cameraState == 1) {

			retSP->Draw();
		}

		if (input->PushKey(DIK_TAB) && cameraState == 2 || cameraState == 3) {
			sprite1->Draw();
		}

		break;
	}


}

void GameScene::Reticle3D() {

	//自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = { 0.0f, 0, -1.0f };

	if (isDireFlag == 1) {
		offset.x = 1.0f;
	}
	else if (isDireFlag == 2) {
		offset.x = -1.0f;
	}
	else {
		offset.x = 0.0f;
	}

	//自機のワールド行列の回転を反映
	offset = Affin::VecMat(offset, player->wtf.matWorld);
	//ベクトルの長さを整える
	offset.nomalize();

	offset *= -100;
	reticle->wtf.position = offset;
	reticle->wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	reticle->wtf.matWorld = Affin::matScale(reticle->wtf.scale);
	reticle->wtf.matWorld = Affin::matTrans(reticle->wtf.position);

	reticle->Update(view);
}

void GameScene::Attack()
{
	if (burstBL < 30) {
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
			//音声再生
			audio->PlayWave("gate.wav");
			burstBL++;

			//クールタイムをリセット
			coolTime = 3;
		}
		else {
			coolTime--;
		}
	}

	if (burstBL >= 30) {
		burstCoolTime = 50;
		burstBL = 0;
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