#include "EnemyBullet.h"



void EnemyBullet::Initialize(Model* model, const Vector3& position, Vector3 vector)
{
	//NULLチェック
	assert(model);
	model_ = model;
	eneVec = vector;
	//eneVec.normalize();

	isDead = false;
	deadCount = 150;

	worldTransform_.Initialize();

	//worldTransform_.scale_ = Vector3(0.5f, 0.5f, 0.5f);
	worldTransform_.position = position;
	worldTransform_.matWorld *= Affin::matWorld(worldTransform_.position, worldTransform_.rotation, worldTransform_.scale);

	worldTransform_.Update();
}

void EnemyBullet::Update()
{
	bulletSpe = eneVec;
	if (isDead==false) {
		if (deadCount > 0) {			

			worldTransform_.position += bulletSpe;

			worldTransform_.matWorld = Affin::matWorld(worldTransform_.position, worldTransform_.rotation, worldTransform_.scale);
			//行列の再計算
			worldTransform_.Update();

			deadCount--;

		}
		else {
			isDead = true;
			deadCount = 150;
		}
	}
}

//void EnemyBullet::Draw(const ViewProjection& viewProjection, uint32_t textureHandle)
//{
//	//モデルの描画
//	model_->Draw(worldTransform_, viewProjection, textureHandle);
//}

void EnemyBullet::OnColision() {
	isDead = true;
}
