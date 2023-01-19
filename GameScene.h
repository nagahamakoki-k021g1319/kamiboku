#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include <string>

#include "Matrix4.h"

#include "Transform.h"
#include "View.h"

#include "object/Enemy.h"
#include "object/Bullet.h"
#include "object/EnemyBullet.h"


/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void Reticle3D();
	void Attack();

	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
		eneBullets_.push_back(std::move(enemyBullet));
	}
	int CheckAlive(Enemy enemys_[]);

private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	Sprite* sprite = new Sprite();
	XMFLOAT2 position = sprite->GetPosition();

	Sprite* sprite1 = new Sprite();
	XMFLOAT2 position1 = sprite1->GetPosition();

	Sprite* sprite2 = new Sprite();
	XMFLOAT2 position2 = sprite2->GetPosition();

	int ischackFlag = 0;

	Object3d* homeOBJ = nullptr;
	Object3d* player = nullptr;
	Object3d* reticle = nullptr;
	Object3d* zango = nullptr;
	Model* model = nullptr;
	Model* model2 = nullptr;
	Model* reticleMD = nullptr;
	Model* zangoMD = nullptr;
	Model* eneMD = nullptr;


	int soundCheckFlag = 0;

	GameScene* gamescene_ = nullptr;

	// �J�����֌W

	View* view = nullptr;
	// ���Ԍv���ɕK�v�ȃf�[�^
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;
	float elapsedTime = 0;

	// ��ԂŎg���f�[�^
	// start -> end �� 5[��] �Ŋ���������
	Vector3 p0, p1, p2, p3;
	//Vector3 p0, p1, p2, p3;
	float maxTime = 50.0f;
	float timeRate;
	float maxTimeRate;
	int cameraState = 0;

	Vector3 ai;

	// 3D���e�B�N���p���[���h�g�����X�t�H�[��
	float kDistancePlayerTo3DReticle = -80.0f;
	Vector3 ret3DPos{0,0,0};
	Vector3 myPos = {0,0,0};
	Vector3 resultRet={0,0,0};

	// �G
	Enemy enemys[50];
	Object3d* PopPos_[5];
	int aliveNum = 0;

	//�e
	std::list<std::unique_ptr<EnemyBullet>> eneBullets_;
	// �G
	int popTime = 0;
	int coolTime = 0;
	int killCounter;
	int popCount = 0;
	int wave = 0;
	int waitTimer = 250;

	//�e
	std::list<std::unique_ptr<Bullet>> bullets_;
	Vector3 pos;
	Vector3 moveBul;
	Vector3 velo;


	float KEyeSpeed = 0.0f;
	float addspeed = 0.0f;


};

