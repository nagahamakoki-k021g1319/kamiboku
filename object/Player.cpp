//#include "Player.h"
//#include "Affin.h"
//#include "Player.h"
//#include "WinApp.h"
//
//
//void Player::Initialize(Model* model,Input* input)
//{
//	// NULL�|�C���^�`�F�b�N
//	assert(model);
//	assert(input);
//	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
//	this->model_ = model;
//	/*this->textureHandle_ = textureHandle;*/
//	// �C���X�^���X���擾����
//	input_ = input;
//	//debugText_ = DebugText::GetInstance();
//	winApp_ = WinApp::GetInstance();
//	// ���[���h�ϊ��̏�����
//	worldTransform_.Initialize();
//	// 3D���e�B�N���̃��[���h�g�����X�t�H�[��������
//	worldTransform3DReticle_.Initialize();
//
//	//// ���e�B�N���p�e�N�X�`���擾
//	//uint32_t textureReticle = TextureManager::Load("2Dreticle.png");
//	//// �X�v���C�g����
//	//sprite2DReticle_.reset(Sprite::Create(
//	//	textureReticle, Vector2(0, 0), Vector4(1, 1, 1, 1), Vector2(0.5f, 0.5f)));
//}
//
//void Player::Update(View* view)
//{
//	Rotate();
//	Move();
//	DeleteBullet();
//	Attack();
//
//	// �e�X�V
//	for (std::unique_ptr<Bullet>& bullet : bullets_) { bullet->Update(view); }
//
//	// ���@�̃��[���h���W����3D���e�B�N���̃��[���h���W���v�Z
//	{
//		// ���@����3D���e�B�N���ւ̋���
//		const float kDistancePlayerTo3DReticle = 50.0f;
//		// ���@����3D���e�B�N���ւ̃I�t�Z�b�g
//		Vector3 offset = { 0, 0, 1.0f };
//		//���@�̃��[���h�s��̉�]�𔽉f
//		offset = Affin::VecMat(offset, worldTransform_.wtf.matWorld);
//		// �x�N�g���̒����𑵂���
//		offset = (offset.nomalize() * kDistancePlayerTo3DReticle);
//		// 3D���e�B�N���̍��W��ݒ�
//		worldTransform3DReticle_.wtf.position = Affin::v(offset, worldTransform_.wtf.matWorld);
//		worldTransform3DReticle_.Update(view);
//	}
//	// 3D���e�B�N���̃��[���h���W����2D���e�B�N���̃X�N���[�����W���v�Z
//	{
//		// 3D���e�B�N���̃��[���h�s�񂩂烏�[���h���W���擾
//		Vector3 positionReticle = Affin::GetWorldTrans(worldTransform3DReticle_.wtf.matWorld);
//		//�r���[�|�[�g�s��
//		Matrix4 matViewport =
//			affine::setViewportMat(worldTransform3DReticle_, winApp_, Vector3(0, 0, 0));
//		//�r���[�s��ƃv���W�F�N�V�����s��A�r���[�|�[�g�s�����������
//		Matrix4 matViewProjectionViewport;
//		matViewProjectionViewport = viewProjection.matView;
//		matViewProjectionViewport *= viewProjection.matProjection;
//		matViewProjectionViewport *= matViewport;
//		// ���[���h���X�N���[�����W�ϊ�(������3D����2D�ɂȂ�)
//		positionReticle = affine::wDivision(positionReticle, matViewProjectionViewport);
//		// �X�v���C�g�̃��e�B�N���ɍ��W�ݒ�
//		sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
//		debugText_->SetPos(50, 190);
//		debugText_->Printf(
//			"positionReticle:(%f,%f)", positionReticle.x, positionReticle.y);
//
//	}
//}
//
//void Player::Draw(ViewProjection viewProjection)
//{
//	model_->Draw(worldTransform_, viewProjection, textureHandle_);
//	//model_->Draw(worldTransform3DReticle_, viewProjection);
//	// �e�`��
//	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
//}
//
//void Player::DrawUI()
//{
//	sprite2DReticle_->Draw();
//}
//
//void Player::Rotate()
//{
//	const float kRotateSpd = 0.02f;
//
//	if (input_->PushKey(DIK_D)) { worldTransform_.rotation_.y -= kRotateSpd; }
//	else if (input_->PushKey(DIK_A)) { worldTransform_.rotation_.y += kRotateSpd; }
//}
//
//void Player::Move()
//{
//	// �L�����N�^�[�̈ړ��x�N�g��
//	Vector3 move = { 0,0,0 };
//	// �L�����N�^�[�ړ��̑���
//	const float kCharacterSpeed = 0.2f;
//	// �����������ňړ��x�N�g����ύX
//	if (input_->PushKey(DIK_LEFT)) { move.x = -kCharacterSpeed; }
//	else if (input_->PushKey(DIK_RIGHT)) { move.x = kCharacterSpeed; }
//
//	if (input_->PushKey(DIK_UP)) { move.y = kCharacterSpeed; }
//	else if (input_->PushKey(DIK_DOWN)) { move.y = -kCharacterSpeed; }
//
//	worldTransform_.translation_ += move;
//	// �������E���W
//	const float kMoveLimitX = 35.0f;
//	const float kMoveLimitY = 19.0f;
//	// �͈͂𒴂��Ȃ�����
//	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
//	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
//	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
//	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
//	FuncProcess::Matrix4(worldTransform_, 0);
//	//// �f�o�b�O�p�\��
//	//debugText_->SetPos(50, 100);
//	//debugText_->Printf(
//	//	"Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
//}
//
//void Player::Attack()
//{
//	if (input_->TriggerKey(DIK_SPACE))
//	{
//		// ���L�����̍��W���R�s�[
//		Vector3 position = worldTransform_.translation_;
//		// �e�̑��x 
//		const float kBulletSpeed = 10.0f;
//		Vector3 velocity(0, 0, kBulletSpeed);
//		velocity = RotationOperator(velocity, worldTransform_);
//		// �e�𐶐����A������
//		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
//		newBullet->Initialize(model_, position, velocity);
//		// �e��o�^����
//		bullets_.push_back(std::move(newBullet));
//
//		// ���@����Ə��I�u�W�F�N�g�ւ̃x�N�g��
//		velocity = worldTransform3DReticle_.translation_ - position;
//		velocity = MathUtility::Vector3Normalize(velocity) * kBulletSpeed;
//	}
//}
//
//void Player::OnCollision() {}
//
//void Player::DeleteBullet()
//{
//	// �f�X�t���O�̗������e���폜
//	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {return bullet->IsDead(); });
//}
//
//Vector3 Player::RotationOperator(Vector3& velocity, WorldTransform& worldTransform)
//{
//	Vector3 result = { 0,0,0 };
//
//	//����
//	result.z = velocity.x * worldTransform.matWorld_.m[0][2] +
//		velocity.y * worldTransform.matWorld_.m[1][2] +
//		velocity.z * worldTransform.matWorld_.m[2][2];
//
//	result.x = velocity.x * worldTransform.matWorld_.m[0][0] +
//		velocity.y * worldTransform.matWorld_.m[1][0] +
//		velocity.z * worldTransform.matWorld_.m[2][0];
//
//	result.y = velocity.x * worldTransform.matWorld_.m[0][1] +
//		velocity.y * worldTransform.matWorld_.m[1][1] +
//		velocity.z * worldTransform.matWorld_.m[2][1];
//
//	return result;
//}
//
//Vector3 Player::GetWorldPosition()
//{
//	//���[���h���W�����邽�߂̕ϐ�
//	Vector3 worldPos;
//
//	//���[���h�s��̕��s�ړ��������擾
//	worldPos.x = worldTransform_.matWorld_.m[3][0];
//	worldPos.y = worldTransform_.matWorld_.m[3][1];
//	worldPos.z = worldTransform_.matWorld_.m[3][2];
//
//	return worldPos;
//}
//
//Matrix4 Player::GetMatrix()
//{
//	return worldTransform_.matWorld_;
//}
