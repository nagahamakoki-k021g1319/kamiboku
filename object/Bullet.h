#pragma once
#include "Model.h"
#include "Input.h"

//#include "DebugText.h"
//#include "ViewProjection.h"
#include <cassert>
//#include "WorldTransform.h"
#include "Object3d.h"

#include "Affin.h"

class Bullet
{
public:
	//~Bullet();
	void Initialize(Model* model, const Vector3& position,Vector3 move);

	void Update(Vector3 trans,View* view);

	void Draw();

	void OnColision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans( obj3d.wtf.matWorld); };

	bool IsDead() const { return isDead; }

public:
	const float speed = 10;
	const int r = 2;
	Object3d obj3d;
private:
	
	Model* model_ = nullptr;
	Vector3 movector;


	bool isDead = false;


};

