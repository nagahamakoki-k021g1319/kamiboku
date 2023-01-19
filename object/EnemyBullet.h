#pragma once
#include "Model.h"

#include "Input.h"
//#include "DebugText.h"
//#include "WorldTransform.h"
//#include "ViewProjection.h"
#include <cassert>
#include "Object3d.h"

#include "Affin.h"

class EnemyBullet
{
public:

	void Initialize(Model* model, const Vector3& position,Vector3 vector);

	void Update(View* view);

	void Draw();

	void OnColision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans(obj3d.wtf.matWorld); };

	bool IsDead() const { return isDead; }

public:
	
	const int r = 1;
	Object3d obj3d;
private:
	
	Model* model_ = nullptr;
	Vector3 eneVec;
	Vector3 bulletSpe/* = Vector3(0, 0, 10)*/;

	int deadCount = 0;
	bool isDead = false;
	float speed = 3;


};

