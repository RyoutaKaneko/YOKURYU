/**
 * @file BossBullet.cpp
 * @brief ボス攻撃に使う弾リスト用クラス
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

class BossBullet : public Object3d
{
public:
	///< summary>
	///初期化
	///</summary>
	void BulletInitialize();

	///< summary>
	///初期化
	///</summary>
	void Update(const Vector3& playerPos_);


	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info) override;


public:
	/// <summary>
	/// 弾存在フラグ
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isDead_; }



private:
	//モデル
	Model* bulletModel = nullptr;

	//速度
	Vector3 playerPos;
	Vector3 velocity;

	//寿命
	static const int32_t kLifeTime = 60 * 8;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	int hp;
	int hitTime;
	bool isHit;
	bool isDead_ = false;

};
