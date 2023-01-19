#include "EnemyBullet.h"



void EnemyBullet::Initialize(Model* model, const Vector3& position, Vector3 vector)
{
	//NULLチェック
	assert(model);
	model_ = model;
	eneVec = vector;
	//eneVec.nomalize();

	isDead = false;
	deadCount = 150;

	obj3d.Initialize();
	obj3d.SetModel(model);
	obj3d.wtf.Initialize();
	obj3d.wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	obj3d.wtf.position = position;
	obj3d.wtf.matWorld *= Affin::matWorld(obj3d.wtf.position, obj3d.wtf.rotation, obj3d.wtf.scale);
}

void EnemyBullet::Update(View* view)
{
	bulletSpe = eneVec;
	if (isDead==false) {
		if (deadCount > 0) {			

			obj3d.wtf.position += bulletSpe;

			obj3d.wtf.matWorld = Affin::matWorld(obj3d.wtf.position, obj3d.wtf.rotation, obj3d.wtf.scale);
			//行列の再計算
			obj3d.Update(view);

			deadCount--;

		}
		else {
			isDead = true;
			deadCount = 150;
		}
	}
}

void EnemyBullet::Draw()
{
	//モデルの描画
	obj3d.Draw();
}

void EnemyBullet::OnColision() {
	isDead = true;
}
