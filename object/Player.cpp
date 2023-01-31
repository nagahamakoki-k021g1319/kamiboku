//#include "Player.h"
//#include "Affin.h"
//#include "Player.h"
//#include "WinApp.h"
//
//
//void Player::Initialize(Model* model,Input* input)
//{
//	// NULLポインタチェック
//	assert(model);
//	assert(input);
//	// 引数として受け取ったデータをメンバ変数に記録する
//	this->model_ = model;
//	/*this->textureHandle_ = textureHandle;*/
//	// インスタンスを取得する
//	input_ = input;
//	//debugText_ = DebugText::GetInstance();
//	winApp_ = WinApp::GetInstance();
//	// ワールド変換の初期化
//	worldTransform_.Initialize();
//	// 3Dレティクルのワールドトランスフォーム初期化
//	worldTransform3DReticle_.Initialize();
//
//	//// レティクル用テクスチャ取得
//	//uint32_t textureReticle = TextureManager::Load("2Dreticle.png");
//	//// スプライト生成
//	//sprite2DReticle_.reset(Sprite::Create(
//	//	textureReticle, Vector2(0, 0), Vector4(1, 1, 1, 1), Vector2(0.5f, 0.5f)));
//}
//
//void Player::Update(View* view)
//{
//	Rotate();
//	Move();
//	DeleteBullet();
//	Attack();
//
//	// 弾更新
//	for (std::unique_ptr<Bullet>& bullet : bullets_) { bullet->Update(view); }
//
//	// 自機のワールド座標から3Dレティクルのワールド座標を計算
//	{
//		// 自機から3Dレティクルへの距離
//		const float kDistancePlayerTo3DReticle = 50.0f;
//		// 自機から3Dレティクルへのオフセット
//		Vector3 offset = { 0, 0, 1.0f };
//		//自機のワールド行列の回転を反映
//		offset = Affin::VecMat(offset, worldTransform_.wtf.matWorld);
//		// ベクトルの長さを揃える
//		offset = (offset.nomalize() * kDistancePlayerTo3DReticle);
//		// 3Dレティクルの座標を設定
//		worldTransform3DReticle_.wtf.position = Affin::v(offset, worldTransform_.wtf.matWorld);
//		worldTransform3DReticle_.Update(view);
//	}
//	// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
//	{
//		// 3Dレティクルのワールド行列からワールド座標を取得
//		Vector3 positionReticle = Affin::GetWorldTrans(worldTransform3DReticle_.wtf.matWorld);
//		//ビューポート行列
//		Matrix4 matViewport =
//			affine::setViewportMat(worldTransform3DReticle_, winApp_, Vector3(0, 0, 0));
//		//ビュー行列とプロジェクション行列、ビューポート行列を合成する
//		Matrix4 matViewProjectionViewport;
//		matViewProjectionViewport = viewProjection.matView;
//		matViewProjectionViewport *= viewProjection.matProjection;
//		matViewProjectionViewport *= matViewport;
//		// ワールド→スクリーン座標変換(ここで3Dから2Dになる)
//		positionReticle = affine::wDivision(positionReticle, matViewProjectionViewport);
//		// スプライトのレティクルに座標設定
//		sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
//		debugText_->SetPos(50, 190);
//		debugText_->Printf(
//			"positionReticle:(%f,%f)", positionReticle.x, positionReticle.y);
//
//	}
//}
//
//void Player::Draw(ViewProjection viewProjection)
//{
//	model_->Draw(worldTransform_, viewProjection, textureHandle_);
//	//model_->Draw(worldTransform3DReticle_, viewProjection);
//	// 弾描画
//	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
//}
//
//void Player::DrawUI()
//{
//	sprite2DReticle_->Draw();
//}
//
//void Player::Rotate()
//{
//	const float kRotateSpd = 0.02f;
//
//	if (input_->PushKey(DIK_D)) { worldTransform_.rotation_.y -= kRotateSpd; }
//	else if (input_->PushKey(DIK_A)) { worldTransform_.rotation_.y += kRotateSpd; }
//}
//
//void Player::Move()
//{
//	// キャラクターの移動ベクトル
//	Vector3 move = { 0,0,0 };
//	// キャラクター移動の速さ
//	const float kCharacterSpeed = 0.2f;
//	// 押した方向で移動ベクトルを変更
//	if (input_->PushKey(DIK_LEFT)) { move.x = -kCharacterSpeed; }
//	else if (input_->PushKey(DIK_RIGHT)) { move.x = kCharacterSpeed; }
//
//	if (input_->PushKey(DIK_UP)) { move.y = kCharacterSpeed; }
//	else if (input_->PushKey(DIK_DOWN)) { move.y = -kCharacterSpeed; }
//
//	worldTransform_.translation_ += move;
//	// 制限限界座標
//	const float kMoveLimitX = 35.0f;
//	const float kMoveLimitY = 19.0f;
//	// 範囲を超えない処理
//	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
//	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
//	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
//	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
//	FuncProcess::Matrix4(worldTransform_, 0);
//	//// デバッグ用表示
//	//debugText_->SetPos(50, 100);
//	//debugText_->Printf(
//	//	"Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
//}
//
//void Player::Attack()
//{
//	if (input_->TriggerKey(DIK_SPACE))
//	{
//		// 自キャラの座標をコピー
//		Vector3 position = worldTransform_.translation_;
//		// 弾の速度 
//		const float kBulletSpeed = 10.0f;
//		Vector3 velocity(0, 0, kBulletSpeed);
//		velocity = RotationOperator(velocity, worldTransform_);
//		// 弾を生成し、初期化
//		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
//		newBullet->Initialize(model_, position, velocity);
//		// 弾を登録する
//		bullets_.push_back(std::move(newBullet));
//
//		// 自機から照準オブジェクトへのベクトル
//		velocity = worldTransform3DReticle_.translation_ - position;
//		velocity = MathUtility::Vector3Normalize(velocity) * kBulletSpeed;
//	}
//}
//
//void Player::OnCollision() {}
//
//void Player::DeleteBullet()
//{
//	// デスフラグの立った弾を削除
//	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead(); });
//}
//
//Vector3 Player::RotationOperator(Vector3& velocity, WorldTransform& worldTransform)
//{
//	Vector3 result = { 0,0,0 };
//
//	//内積
//	result.z = velocity.x * worldTransform.matWorld_.m[0][2] +
//		velocity.y * worldTransform.matWorld_.m[1][2] +
//		velocity.z * worldTransform.matWorld_.m[2][2];
//
//	result.x = velocity.x * worldTransform.matWorld_.m[0][0] +
//		velocity.y * worldTransform.matWorld_.m[1][0] +
//		velocity.z * worldTransform.matWorld_.m[2][0];
//
//	result.y = velocity.x * worldTransform.matWorld_.m[0][1] +
//		velocity.y * worldTransform.matWorld_.m[1][1] +
//		velocity.z * worldTransform.matWorld_.m[2][1];
//
//	return result;
//}
//
//Vector3 Player::GetWorldPosition()
//{
//	//ワールド座標を入れるための変数
//	Vector3 worldPos;
//
//	//ワールド行列の平行移動成分を取得
//	worldPos.x = worldTransform_.matWorld_.m[3][0];
//	worldPos.y = worldTransform_.matWorld_.m[3][1];
//	worldPos.z = worldTransform_.matWorld_.m[3][2];
//
//	return worldPos;
//}
//
//Matrix4 Player::GetMatrix()
//{
//	return worldTransform_.matWorld_;
//}
