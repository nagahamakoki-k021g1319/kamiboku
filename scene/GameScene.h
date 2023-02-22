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
#include "ConvertXM.h"

#include "Transform.h"

#include "object/Enemy.h"
#include "object/Bullet.h"
#include "object/EnemyBullet.h"

#include "DebugCamera.h"
#include "FBX/FBXObject3d.h"
#include "FBX/FbxLoader.h"

#include "Particle/ParticleManager.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, GameScene* gamescene);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Reticle3D();
	void Attack();

	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) {
		eneBullets_.push_back(std::move(enemyBullet));
	}
	int CheckAlive(Enemy enemys_[]);
public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };


private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	//FBXで使うカメラ(ビュープロジェクション?みたいな)
	DebugCamera* camera = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Audio* audio = nullptr;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* sprite = new Sprite();
	XMFLOAT2 position = sprite->GetPosition();

	Sprite* sprite1 = new Sprite();
	XMFLOAT2 position1 = sprite1->GetPosition();

	Sprite* sprite2 = new Sprite();
	XMFLOAT2 position2 = sprite2->GetPosition();

	Sprite* clearSP = new Sprite();
	XMFLOAT2 clearPOS = clearSP->GetPosition();

	Sprite* titleSP = new Sprite();
	XMFLOAT2 titlePOS = titleSP->GetPosition();
	Sprite* endSP = new Sprite();
	XMFLOAT2 endPOS = endSP->GetPosition();

	Sprite* retSP = new Sprite();
	XMFLOAT2 retPOS = retSP->GetPosition();


	int ischackFlag = 0;

	Object3d* homeOBJ = nullptr;
	Object3d* player = nullptr;
	Object3d* reticle = nullptr;
	Object3d* zango = nullptr;
	Object3d* floor = nullptr;
	Object3d* skydome = nullptr;
	Model* model = nullptr;
	Model* model2 = nullptr;
	Model* reticleMD = nullptr;
	Model* zangoMD = nullptr;
	Model* eneMD = nullptr;
	Model* floorMD = nullptr;
	Model* skydomeMD = nullptr;
	int eneChangeFlag = 0;
	int eneChangeTimer = 0;

	FBXModel* fbxModel_ = nullptr;
	FBXObject3d* fbxObject3d_ = nullptr;
	FBXModel* fbxModel2_ = nullptr;
	FBXObject3d* fbxObject3d_2 = nullptr;

	GameScene* gamescene_ = nullptr;

	// 時間計測に必要なデータ
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;
	float elapsedTime = 0;

	// 補間で使うデータ
	// start -> end を 5[ｓ] で完了させる
	Vector3 p0, p1, p2, p3;
	//Vector3 p0, p1, p2, p3;
	float maxTime = 50.0f;
	float timeRate;
	float maxTimeRate;
	bool isMove;
	int cameraState = 0;
	const float FLMAX = 90, FLMIN = 20;
	const Vector3 MAXVec3 = { 0,150,0 }, MINVec3 = { 0,0,0 };
	Vector3 ai;
	bool isUP=false;

	// 3Dレティクル用ワールドトランスフォーム
	float kDistancePlayerTo3DReticle = -80.0f;
	Vector3 ret3DPos{ 0,0,0 };
	Vector3 myPos = { 0,0,0 };
	Vector3 resultRet = { 0,0,0 };

	// 敵
	Enemy enemys[70];
	Object3d* PopPos_[5];
	int aliveNum = 0;

	//弾
	std::list<std::unique_ptr<EnemyBullet>> eneBullets_;

	// 敵
	int popTime = 0;
	int coolTime = 0;
	int killCounter = 0;
	int popCount = 0;
	int wave = 0;
	int waitTimer = 250;

	//自弾
	std::list<std::unique_ptr<Bullet>> bullets_;
	Vector3 pos;
	Vector3 moveBul;
	Vector3 velo;
	int	burstBL = 0;
	int burstCoolTime = 0;


	float KEyeSpeed = 0.0f;
	float addspeed = 0.0f;

	int scene = 0;

	//パーティクルクラスの初期化 
	ParticleManager* particleManager = nullptr;
	int PTtime = 0;
	bool isPTflag = false;

	//左右のオフセット変更(Z + 向き) 左がフラグ1 左がフラグ2
	int isDireFlag = 0;

	int isHit;
	int HP = 15;
	//左右移動してる時は頭はだせない
	int isAction = 0;


	//UIで使うやつまとめ
	//右
	Sprite* sprite3 = new Sprite();
	XMFLOAT2 position3 = sprite3->GetPosition();
	Sprite* sprite4 = new Sprite();
	XMFLOAT2 position4 = sprite4->GetPosition();
	int isLeftFlag = 0;

	//左
	Sprite* sprite5 = new Sprite();
	XMFLOAT2 position5 = sprite5->GetPosition();
	Sprite* sprite6 = new Sprite();
	XMFLOAT2 position6 = sprite6->GetPosition();
	int isRightFlag = 0;

	//上
	Sprite* sprite8 = new Sprite();
	XMFLOAT2 position8 = sprite8->GetPosition();
	Sprite* sprite9 = new Sprite();
	XMFLOAT2 position9 = sprite9->GetPosition();
	int isUpFlag = 0;

	//コンパス
	Sprite* sprite7 = new Sprite();
	XMFLOAT2 position7 = sprite7->GetPosition();
	Sprite* sprite15 = new Sprite();
	XMFLOAT2 position15 = sprite15->GetPosition();
	float rotatte = 0;



	//切り替えボタン
	Sprite* sprite10 = new Sprite();
	XMFLOAT2 position10 = sprite10->GetPosition();
	Sprite* sprite16 = new Sprite();
	XMFLOAT2 position16 = sprite16->GetPosition();


	//ブラックアウト
	Sprite* sprite12 = new Sprite();
	XMFLOAT2 position12 = sprite12->GetPosition();
	Sprite* sprite13 = new Sprite();
	XMFLOAT2 position13 = sprite13->GetPosition();
	Sprite* sprite14 = new Sprite();
	XMFLOAT2 position14 = sprite14->GetPosition();
	int isSHFlag = 0;
	int SHtimer = 0;


	//音関係まとめ
	int isDrornFlag = 0;
	int isChangeDrornTimer = 0;
	int isChangeDrornTimer2 = 0;
	int soundCheckFlag = 0;
	int soundCheckFlag2 = 0;
};

