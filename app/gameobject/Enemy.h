/**
 * @file Enemy.cpp
 * @brief enemyの全般(ステータス、行動、描画)をまとめたクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>
#include "EnemyBullet.h"
#include "Energy.h"
#include "RailCamera.h"

//GameSceneの前方宣言
class GameScene;

class Enemy : public Object3d
{
public:
	//デストラクタ
	~Enemy();
	
	/// <summary>
	/// 初期化
	/// </summary>
	void EnemyInitialize();

	/// <summary>
	/// 死亡フラグを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead_; }
	
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="velo">弾ベクトル</param>
	/// <param name="t">プレイヤー通過点</param>
	void Update(Vector3 velo,RailCamera* rail);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection_">カメラ</param>
	void EnemyDraw(ViewProjection* viewProjection_);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info) override;

	/// <summary>
	///  出現位置を設定
	/// </summary>
	/// <param name="pos_">出現位置</param>
	void SetStagePoint(float pos_) { stagePoint = pos_; }

	/// <summary>
	/// 出現位置を取得
	/// </summary>
	/// <returns></returns>
	float GetStagePoint(){return stagePoint;}

	/// <summary>
	/// 敵オブジェクトポインタを取得
	/// </summary>
	/// <returns></returns>
	Object3d* GetPointer() { return this; }

	/// <summary>
	/// 敵出現状態を取得
	/// </summary>
	/// <returns></returns>
	bool GetIsInvisible() { return isInvisible; }

	/// <summary>
	/// 弾リストを取得
	/// </summary>
	/// <returns></returns>
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

	/// <summary>
	/// 死亡演出
	/// </summary>
	void PopParticle();

	bool GetIsParticle() { return isParticle; }

private:

	static const int DEATH_TIMER = 60;

	//デスフラグ
	bool isDead_ = false;
	//
	bool isInvisible = true;
	bool isParticle = false;

	//敵
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	std::list<std::unique_ptr<Energy>> deadParticles;

	// モデル
	Model* enemyModel = nullptr;
	float alpha;

	//半径
	int timer;
	float radius = 1.0f;
	int coolTime = 0;
	float stagePoint;
	int deathTimer;

	bool isAttack;
	int timeCount;
};
