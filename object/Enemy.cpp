#include "Enemy.h"
#include <cassert>



Enemy::Enemy() {
	worldTransForm.Initialize();
	worldTransForm.wtf.position = { 100,0,100 };
	isDead = true;
	YTmp = { 0,1,0 };
	speed = 0.0004f;
	worldTransForm.wtf.matWorld = Affin::matUnit();
}

Enemy::~Enemy() {}

void Enemy::CalcVec(Vector3 obj) {
	//���ʉ��x�N�g��
	enemyTmp = obj - worldTransForm.wtf.position;
	enemyTmp.nomalize();
	//�E�x�N�g��
	enemyRight = YTmp.cross(enemyTmp);
	enemyRight.nomalize();
	//���ʃx�N�g��
	enemyFront = enemyRight.cross(YTmp);
	enemyFront.nomalize();
}

void Enemy::Update(Model* model_, Vector3 obj,View& view) {
	assert(model_);
	////�f�X�t���O�̗������e���폜
	//bullets_.remove_if(
	//	[](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });


	//�x�N�g���v�Z
	CalcVec(obj);
	if (coolTime == 0) {
		Attack(model_);
	}
	else {
		coolTime--;
	}
	////�e�`��
	//for (std::unique_ptr<EnemyBullet>& Ebullet : bullets_) {
	//	if (Ebullet->IsDead()==false) {
	//		Ebullet->Update();
	//	}
	//}

	//�s��v�Z

	worldTransForm.wtf.matWorld = Affin::matWorld(
		worldTransForm.wtf.position,
		worldTransForm.wtf.rotation,
		worldTransForm.wtf.scale);

	if (isDead == false) {
		time++;
		if (time == 6) {
			speed += 0.0001f;
			time = 0;
		}
		worldTransForm.wtf.position += enemyFront * 0.1;
	}
	else if (isDead == true) {
		speed = 0.0008f;
		time = 0;
	}

	switch (seed_)
	{
	case 1:
		if (worldTransForm.wtf.position.x < 90) {
			worldTransForm.wtf.position.x = 90;
		}
		break;
	case 2:
		if (worldTransForm.wtf.position.x > -90) {
			worldTransForm.wtf.position.x = -90;
		}
		break;
	case 3:
		if (worldTransForm.wtf.position.z < 90) {
			worldTransForm.wtf.position.z = 90;
		}
		break;
	case 4:
		if (worldTransForm.wtf.position.z > -90) {
			worldTransForm.wtf.position.z = -90;
		}
		break;

	default:
		break;
	}



	//���ʂ𔽉f
	worldTransForm.Update(&view);
	
	//Hit();
}

//void Enemy::Draw() {	
//	////�e�`��
//	//for (std::unique_ptr<EnemyBullet>& Ebullet : bullets_) {
//	//	Ebullet->Draw(viewProjection_, textureHandle_);
//	//}
//}

void Enemy::Pop(Vector3 WorTrans, int seed) {
	worldTransForm.Initialize();
	worldTransForm.wtf.position = { 100,0,100 };
	YTmp = { 0,1,0 };
	worldTransForm.wtf.matWorld =Affin::matUnit();

	if (isDead == true) {
		isDead = false;
		seed_ = seed;

		//�����������u
		std::random_device seed_gen;
		std::mt19937_64 engine(seed_gen());
		std::uniform_real_distribution<float>dist(20.0f, 50.0f);
		std::uniform_real_distribution<float>dist2(-1.0f, 1.0f);

		//����
		float value = dist(engine) * dist2(engine);

		//
		worldTransForm.wtf.position = { WorTrans.x + value,WorTrans.y, WorTrans.z + value };
	}
}

void Enemy::Hit() {
	if (worldTransForm.wtf.position.x < 0.5 && worldTransForm.wtf.position.x > -0.5) {
		if (worldTransForm.wtf.position.z < 0.5 && worldTransForm.wtf.position.z > -0.5) {
			if (isDead == false) {
				isDead = true;
			}
		}
	}
}

void Enemy::OnColision() {
	isDead = true;
}

void Enemy::Attack(Model* model_)
{
	assert(model_);
	Vector3 pos;


	if (isDead == false) {
		//�e�𐶐����A������
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		//Bullet* newbullet = new Bullet();

		pos = worldTransForm.wtf.position;

		newBullet->Initialize(model_, pos, enemyFront);

		////�e��o�^
		////bullets_.push_back(std::move(newBullet));
		//gameScene->AddEnemyBullet(std::move(newBullet));

		//�N�[���^�C�������Z�b�g
		coolTime = 250;

	}
}
