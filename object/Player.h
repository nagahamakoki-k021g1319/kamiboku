//#pragma once
//
////#include "FunctionProcess.h"
//#include "Sprite.h"
//#include "Input.h"
//#include "Matrix4.h"
//#include "Model.h"
//#include "Bullet.h"
//#include "math.h"
//#include <cassert>
//#include <memory>
//#include <list>
//
//#include "View.h"
//#include "Transform.h"
//#include "Object3d.h"
//
//class Player
//{
//public:
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	/// <param name = "model" > モデル </param>
//	/// <param name = "textureHamdle" > テクスチャハンドル </param>
//	void Initialize(Model* model,Input* input);
//
//	/// <summary>
//	/// 更新
//	/// </summary>
//	void Update(View* viewProjection);
//
//	/// <summary>
//	/// 描画
//	/// </summary>
//	void Draw();
//
//	/// <summary>
//	/// UI描画
//	/// </summary>
//	void DrawUI();
//
//	// 旋回
//	void Rotate();
//	// 移動
//	void Move();
//	// 攻撃
//	void Attack();
//
//	//衝突を検出したら呼び出されるコールバック関数
//	void OnCollision();
//
//	void DeleteBullet();
//
//	//タマリストを取得
//	const std::list<std::unique_ptr<Bullet>>& GetBulletd() { return bullets_; }
//
//	Vector3 RotationOperator(Vector3& velocity, Transform& worldTransform);
//	// ワールド座標を取得
//	Vector3 GetWorldPosition();
//
//	Matrix4 GetMatrix();
//
//
//private:
//	Input* input_ = nullptr;
//	//DebugText* debugText_ = nullptr;
//	WinApp* winApp_ = nullptr;
//
//	// ビュープロダクション
//	//ViewProjection viewProjection_;
//	// ワールド変換データ
//	Object3d worldTransform_;
//	// モデル
//	Model* model_ = nullptr;
//	// テクスチャハンドル
//	uint32_t textureHandle_ = 0u;
//
//	// 弾
//	std::list<std::unique_ptr<Bullet>> bullets_;
//
//	// 3Dレティクル用
//	Object3d worldTransform3DReticle_;
//	// 2Dレティクル用スプライト
//	std::unique_ptr<Sprite> sprite2DReticle_;
//};
//
//
