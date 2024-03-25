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

namespace MyEngine {
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
		void Update(const Vector3& velo, MyEngine::RailCamera* rail);

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
		float GetStagePoint() { return stagePoint; }

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
		const std::list<std::unique_ptr<MyEngine::EnemyBullet>>& GetBullets() { return bullets_; }

		/// <summary>
		/// 死亡演出
		/// </summary>
		void PopParticle();

		//ヒット判定
		bool GetIsHit() { return isHit; }

		//定数
	protected:
		static const int DEATH_TIMER = 50;
		static const float MOVE_POWER;
		static const float UPDOWN_POWER;
		static const float MAX_ALPHA;
		static const Vector3 ADDSCALE;
		static const float ATTACK_RANGE;
		static const int COOLTIME_MAX = 200;
		static const int SCALE_MAX = 3;
		static const int DEAD_PARTICLE = 45;
		static const int MOVE_TIME_ONE = 75;
		static const int MOVE_TIME_TWO = 150;
		static const int TIMECOUNT_MAX = 4;
		static const float POP_RANGE;
		static const float SHADOW_Y;

	protected:

		//デスフラグ
		bool isDead_ = false;
		bool isHit = false;
		//
		bool isInvisible = true;
		bool isParticle = false;

		//敵
		std::list<std::unique_ptr<MyEngine::EnemyBullet>> bullets_;
		std::list<std::unique_ptr<MyEngine::Energy>> deadParticles;
		Object3d* shadow = nullptr;

		// モデル
		Model* enemyModel = nullptr;
		Model* shadowModel = nullptr;
		float alpha;

		//半径
		int timer;
		float radius = 1.0f;
		int coolTime = 0;
		float stagePoint;
		int deathTimer;
		float subAlpha = 0.2f;
		Vector3 rotePower;

		bool isAttack;
		int timeCount;
	};
}
