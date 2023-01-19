#include "Bullet.h"

//Bullet::~Bullet() {
//	delete obj3d;
//}
void Bullet::Initialize(Model* model, const Vector3& position,Vector3 move)
{
	//NULL�`�F�b�N
	assert(model);
	model_ = model;

	obj3d.Initialize();
	obj3d.wtf.Initialize();
	obj3d.SetModel(model);
	movector = move;

	//obj3d.translation_ = position;
	obj3d.wtf.matWorld = Affin::matScale(0.5f, 0.5f, 0.5f);
	obj3d.wtf.matWorld = Affin::matTrans(position);
	//obj3d.Update();
}

void Bullet::Update(Vector3 trans,View* view)
{

	obj3d.wtf.position += movector;
	//�s��̍Čv�Z
	obj3d.Update(view);
}

void Bullet::Draw()
{
	//���f���̕`��
	obj3d.Draw();
}

void Bullet::OnColision() {
	isDead = true;
}
