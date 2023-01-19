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

	obj3d.wtf.scale = Vector3(0.5f, 0.5f, 0.5f);
	obj3d.wtf.position = position;
}

void Bullet::Update(Vector3 trans,View* view)
{

	obj3d.wtf.position += (movector*1.5f);
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
