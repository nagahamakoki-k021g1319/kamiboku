#pragma once

#include "WorldTransform.h"
#include "Affin.h"
#include <random>

#include "EnemyBullet.h"

class GameScene;

class Enemy {
public:
	WorldTransform worldTransForm;
	bool isDead = true;
	Vector3 enemyTmp;
	Vector3 YTmp;
	//�E�x�N�g��
	Vector3 enemyRight;
	//���x�N�g��
	Vector3 enemyLeft;
	//���ʃx�N�g��
	Vector3 enemyFront;
	//����
	float speed;
	//time
	int time = 0;
	int seed_ = 0;

	int bulletcoolTime = 50;

	int r = 2;
	int coolTime = 250;

	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	GameScene* gameScene = nullptr;

public:
	Enemy();
	~Enemy();

	void Update(Model*model_,Vector3 obj);
	void Draw(ViewProjection& viewProjection_, uint32_t textureHandle_);
	
	void CalcVec(Vector3 view);
	void Pop(Vector3 WorTrans, int seed_);
	void Hit();
	Vector3 GetWorldPosition() { return Affin::GetWorldTrans(worldTransForm.matWorld_); };
	Vector3 GetFrontVec() { return enemyFront; };
	void SetGameScene(GameScene* gameScene_) { gameScene = gameScene_; };
	void OnColision();
	bool IsDead() const { return isDead; };
	void Attack(Model* model_);
};