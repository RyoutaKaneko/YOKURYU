/**
 * @file Player.cpp
 * @brief プレイヤーの移動、攻撃、描画をまとめたクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"
#include "Particle.h"
#include "PlayerBullet.h"

struct LockInfo {
	Vector3 vec = {0,0,0};
	 Object3d* obj = nullptr;
};

class Player : public Object3d
{
private:
	//体力状況
	enum Health {
		FINE,
		WEEKNESS,
		DYING
	};

public:
	//デストラクタ
	~Player();
	
	/// <summary>
	///	初期化
	/// </summary>
	/// <returns></returns>
	bool PlayerInitialize();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="velo">弾ベクトル</param>
	/// <param name="info">ロックオン情報</param>
	void Update(Vector3 velo, std::vector<LockInfo>& info);

	/// <summary>
	/// 移動
	/// </summary>
	void Move();
	
	/// <summary>
	/// 攻撃
	/// </summary>
	/// <param name="velo">弾ベクトル</param>
	void Attack(Vector3 velo);
	
	/// <summary>
	/// ロックオン攻撃
	/// </summary>
	/// <param name="info">ロックオン情報</param>
	void LockAttack(std::vector<LockInfo>& info);

	/// <summary>
	/// 必殺技
	/// </summary>
	void Ultimate();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection_"></param>
	void PlayerDraw(ViewProjection* viewProjection_);

	/// <summary>
	/// レールに戻る
	/// </summary>
	void BackRail();

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info) override;


	/////getter/////
	
	/// <summary>
	/// hp
	/// </summary>
	/// <returns></returns>
	float GetHP() { return hp; }

	/// <summary>
	/// 必殺技エネルギー
	/// </summary>
	/// <returns></returns>
	float GetEnergy() { return energy; }

	/// <summary>
	/// 攻撃をくらったかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsHit() { return isHit; }
	
	/// <summary>
	/// 攻撃したかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsShooted() { return isShooted; }

	/// <summary>
	/// カメラとの距離
	/// </summary>
	/// <returns></returns>
	float GetLen() { return len; }

	/// <summary>
	/// 必殺技中かどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsUltimate() { return isUltimate; }

	/// <summary>
	/// 移動量
	/// </summary>
	/// <returns></returns>
	Vector3 GetMove() { return move; }

	/// <summary>
	/// 体力状況を取得
	/// </summary>
	/// <returns></returns>
	Health GetHealthState() { return healthState; }

	/////setter/////
	
	/// <summary>
	/// 攻撃をくらったかどうか
	/// </summary>
	/// <param name="isHit_">hitフラグ</param>
	void SetIsHit(bool isHit_) { isHit = isHit_; }

	/// <summary>
	/// 透過度を設定
	/// </summary>
	/// <param name="alpha_">透過度</param>
	void SetAlpha(float alpha_) { alpha = alpha_; }

	/// <summary>
	/// 必殺技
	/// </summary>
	/// <param name="ult">必殺技フラグ</param>
	void SetIsUltimate(bool ult) { isUltimate = ult; }

	/// <summary>
	/// 弾リストを取得
	/// </summary>
	/// <returns></returns>
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }


private:
	Input* input = nullptr;
	// モデル
	Model* playerModel = nullptr;
	//パーティクル
	Particle* particle = nullptr;
	//弾 
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	//HP
	float hp;
	int coolTime = 0;
	float len = 6;
	int pTimer = 0;
	bool isHit;
	bool isShooted;
	int hitTime;
	float alpha;
	float energy;
	bool isUltimate;
	int ultTime;
	Vector3 pos_;
	Vector3 rot_;
	Vector3 move;
	Health healthState;
};
