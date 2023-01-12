#include "Bullet.h"


void Bullet::Initialize(Model* model, const Vector3& position)
{
	//NULL�`�F�b�N
	assert(model);
	model_ = model;

	worldTransform_.Initialize();

	//worldTransform_.translation_ = position;
	worldTransform_.matWorld_ = Affin::matScale(0.5f, 0.5f, 0.5f);
	worldTransform_.matWorld_ = Affin::matTrans(position);
	worldTransform_.TransferMatrix();
}

void Bullet::Update(Vector3 trans)
{

	worldTransform_.matWorld_ *= Affin::matTrans(trans);
	//�s��̍Čv�Z
	worldTransform_.TransferMatrix();
}

void Bullet::Draw(const ViewProjection& viewProjection,uint32_t textureHandle)
{
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle);
}

void Bullet::OnColision() {
	isDead = true;
}
