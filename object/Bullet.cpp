#include "Bullet.h"


void Bullet::Initialize(Model* model, const Vector3& position)
{
	//NULLチェック
	assert(model);
	model_ = model;

	worldTransform_.Initialize();

	//worldTransform_.translation_ = position;
	worldTransform_.wtf.matWorld = Affin::matScale(0.5f, 0.5f, 0.5f);
	worldTransform_.wtf.matWorld = Affin::matTrans(position);
	//worldTransform_.Update();
}

void Bullet::Update(Vector3 trans,View& view)
{

	worldTransform_.wtf.matWorld *= Affin::matTrans(trans);
	//行列の再計算
	worldTransform_.Update(&view);
}

//void Bullet::Draw(const ViewProjection& viewProjection,uint32_t textureHandle)
//{
//	//モデルの描画
//	model_->Draw(worldTransform_, viewProjection, textureHandle);
//}

void Bullet::OnColision() {
	isDead = true;
}
