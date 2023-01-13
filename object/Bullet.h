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

	void Initialize(Model* model, const Vector3& position);

	void Update(Vector3 trans);

	//void Draw(const ViewProjection& viewProjection, uint32_t textureHandle);

	void OnColision();

	Vector3 GetWorldPosition() { return Affin::GetWorldTrans( worldTransform_.matWorld); };

	bool IsDead() const { return isDead; }

public:
	const float speed = 100;
	const int r = 2;
private:
	Object3d worldTransform_;
	Model* model_ = nullptr;


	bool isDead = false;


};

