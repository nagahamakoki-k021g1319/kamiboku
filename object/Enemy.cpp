#include "Enemy.h"
#include <cassert>
#include "GameScene.h"


Enemy::Enemy() {
	obj3d.Initialize();
	obj3d.wtf.position = { 100,0,100 };
	isDead = true;
	YTmp = { 0,1,0 };
	speed = 0.0004f;
	obj3d.wtf.matWorld = Affin::matUnit();
}

Enemy::~Enemy() {}

void Enemy::CalcVec(Vector3 obj) {
	//正面仮ベクトル
	enemyTmp = obj - obj3d.wtf.position;
	enemyTmp.nomalize();
	//右ベクトル
	enemyRight = YTmp.cross(enemyTmp);
	enemyRight.nomalize();
	//正面ベクトル
	enemyFront = enemyRight.cross(YTmp);
	enemyFront.nomalize();
}

void Enemy::Update(Model* model_, Vector3 obj,View* view) {
	assert(model_);

	//ベクトル計算
	CalcVec(obj);
	if (coolTime == 0) {
		Attack(model_);
	}
	else {
		coolTime--;
	}
	//行列計算

	obj3d.wtf.matWorld = Affin::matWorld(
		obj3d.wtf.position,
		obj3d.wtf.rotation,
		obj3d.wtf.scale);

	if (isDead == false) {
		time++;
		if (time == 6) {
			speed += 0.0001f;
			time = 0;
		}
		obj3d.wtf.position += enemyFront * 0.1;
	}
	else if (isDead == true) {
		speed = 0.0008f;
		time = 0;
	}

	switch (seed_)
	{
	case 1:
		if (obj3d.wtf.position.x < 90) {
			obj3d.wtf.position.x = 90;
		}
		break;
	case 2:
		if (obj3d.wtf.position.x > -90) {
			obj3d.wtf.position.x = -90;
		}
		break;
	case 3:
		if (obj3d.wtf.position.z < 90) {
			obj3d.wtf.position.z = 90;
		}
		break;
	case 4:
		if (obj3d.wtf.position.z > -90) {
			obj3d.wtf.position.z = -90;
		}
		break;

	default:
		break;
	}

	//結果を反映
	obj3d.Update(view);
}

void Enemy::Pop(Vector3 WorTrans, int seed, Model* model) {
	//obj3d = Object3d::Create();
	obj3d.Initialize();
	obj3d.SetModel(model);
	obj3d.wtf.Initialize();
	obj3d.wtf.position = { 100,0,100 };
	obj3d.wtf.rotation = { 0,0,0 };
	obj3d.wtf.scale = { 1,1,1 };
	YTmp = { 0,1,0 };
	obj3d.wtf.matWorld =Affin::matUnit();

	if (isDead == true) {
		isDead = false;
		seed_ = seed;

		//乱数生成装置
		std::random_device seed_gen;
		std::mt19937_64 engine(seed_gen());
		std::uniform_real_distribution<float>dist(20.0f, 50.0f);
		std::uniform_real_distribution<float>dist2(-1.0f, 1.0f);

		//乱数
		float value = dist(engine) * dist2(engine);

		//
		obj3d.wtf.position = { WorTrans.x + value,WorTrans.y, WorTrans.z + value };
	}
}

void Enemy::Hit() {
	if (obj3d.wtf.position.x < 0.5 && obj3d.wtf.position.x > -0.5) {
		if (obj3d.wtf.position.z < 0.5 && obj3d.wtf.position.z > -0.5) {
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
		//弾を生成し、初期化
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		//Bullet* newbullet = new Bullet();

		pos = obj3d.wtf.position;

		newBullet->Initialize(model_, pos, enemyFront);

		//弾を登録
		//bullets_.push_back(std::move(newBullet));
		gameScene->AddEnemyBullet(std::move(newBullet));

		//クールタイムをリセット
		coolTime = 250;

	}
}

void Enemy::Draw() {
	obj3d.Draw();
}