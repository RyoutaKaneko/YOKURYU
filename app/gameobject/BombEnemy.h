/**
 * @file BombEnemy.h
 * @brief 突っ込んできて爆発する敵クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Enemy.h"
#include "BaseCollider.h"

namespace MyEngine {
	class BombEnemy : public Enemy
	{
	public:
		~BombEnemy();

		/// <summary>
		/// 初期化
		/// </summary>
		void BombInitialize();

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="velo">player座標</param>
		/// <param name="t">プレイヤー通過点</param>
		void BombUpdate(const Vector3& pPos, MyEngine::RailCamera* rail);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="viewProjection_">カメラ</param>
		void BombDraw(ViewProjection* viewProjection_);

		/// <summary>
		/// 攻撃
		/// </summary>
		void BombAttack(const Vector3& pPos);

		/// <summary>
		/// 当たり判定
		/// </summary>
		/// <param name="info">衝突情報</param>
		void OnCollision(const CollisionInfo& info) override;

	private:
		float popTime;
	};
}

