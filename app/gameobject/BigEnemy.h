/**
 * @file BigEnemy.h
 * @brief でか敵クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Enemy.h"
#include "BaseCollider.h"

namespace MyEngine {
	class BigEnemy : public Enemy
	{
	public:
		~BigEnemy();

		/// <summary>
		/// 初期化
		/// </summary>
		void BigInitialize();

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="velo">player座標</param>
		/// <param name="t">プレイヤー通過点</param>
		void BigUpdate(const Vector3& pPos, MyEngine::RailCamera* rail);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="viewProjection_">カメラ</param>
		void BigDraw(ViewProjection* viewProjection_);

		/// <summary>
		/// 当たり判定
		/// </summary>
		/// <param name="info">衝突情報</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// 死亡時敵生成
		/// </summary>
		bool GetPopReq() { return popReq; }

		/// <summary>
		/// 死亡時敵生成
		/// </summary>
		void SetPopReq(const bool& req) { popReq = req; }

	private:
		bool popReq;
	};
}



