#pragma once
#include "Vector3.h"
#include <Model.h>
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include "Object3d.h"

class PlayerBullet : public Object3d 
{
  public:
	///< summary>
	///初期化
	///</summary>
	void BulletInitialize(const Vector3& position, const Vector3& velocity);

	///< summary>
	///初期化
	///</summary>
	void Update();


	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision(const CollisionInfo& info) override;


  public:
	bool IsDead() const { return isDead_; }
	WorldTransform* GetWorldTransForm() { return &worldTransform_; }

  private:
	//モデル
	Model* bulletModel = nullptr;
	
	//速度
	Vector3 velocity_;
	
	//寿命
	static const int32_t kLifeTime = 60 * 3;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	
};
