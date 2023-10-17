/**
 * @file PlayerBullet.cpp
 * @brief プレイヤーの攻撃に使う弾リスト用クラス
 * @author カネコ_リョウタ
 */

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
	void BulletInitialize(const Vector3& velocity);

	///< summary>
	///初期化
	///</summary>
	void Update();

	/// <summary>
	///ホーミング弾ベクトル
	/// </summary>
	void HomingVec();

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info) override;


  public:
	/// <summary>
	/// 死亡フラグ取得
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// ワールドトランスフォームを取得
	/// </summary>
	/// <returns></returns>
	WorldTransform* GetWorldTransForm() { return &worldTransform_; }

	/// <summary>
	/// ホーミング攻撃かどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsHoming() { return isHoming; }
	
	/// <summary>
	/// ホーミング攻撃かどうか
	/// </summary>
	/// <param name="isHoming_"></param>
	void SetisHoming(bool isHoming_) { isHoming = isHoming_; }

	/// <summary>
	/// ロックオン情報を設定
	/// </summary>
	/// <param name="obj"></param>
	void SetLock(Object3d* obj) { lockObj = obj; }

  private:
	//モデル
	Model* bulletModel = nullptr;
	
	//速度
	Vector3 velocity_;
	
	//寿命
	static const int32_t kLifeTime = 60 * 8;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	bool isHoming = false;
	Object3d* lockObj = nullptr;
};
