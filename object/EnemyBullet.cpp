#include "EnemyBullet.h"



void EnemyBullet::Initialize(Model* model, const Vector3& position, Vector3 vector)
{
	//NULL�`�F�b�N
	assert(model);
	model_ = model;
	eneVec = vector;
	//eneVec.normalize();

	isDead = false;
	deadCount = 150;

	worldTransform_.Initialize();

	//worldTransform_.scale_ = Vector3(0.5f, 0.5f, 0.5f);
	worldTransform_.wtf.position = position;
	worldTransform_.wtf.matWorld *= Affin::matWorld(worldTransform_.wtf.position, worldTransform_.wtf.rotation, worldTransform_.wtf.scale);

	//worldTransform_.Update();
}

void EnemyBullet::Update(View& view)
{
	bulletSpe = eneVec;
	if (isDead==false) {
		if (deadCount > 0) {			

			worldTransform_.wtf.position += bulletSpe;

			worldTransform_.wtf.matWorld = Affin::matWorld(worldTransform_.wtf.position, worldTransform_.wtf.rotation, worldTransform_.wtf.scale);
			//�s��̍Čv�Z
			worldTransform_.Update(&view);

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
//	//���f���̕`��
//	model_->Draw(worldTransform_, viewProjection, textureHandle);
//}

void EnemyBullet::OnColision() {
	isDead = true;
}
