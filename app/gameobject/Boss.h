/**
 * @file Boss.cpp
 * @brief ボス全般(ステータス、行動、描画)をまとめたもの
 * @author カネコ_リョウタ
 */

#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include "BossBullet.h"

//GameSceneの前方宣言
class GameScene;

namespace MyEngine {
	class Boss : public Object3d
	{
	public:
		//デストラクタ
		~Boss();

		/// <summary>
		/// 初期化
		/// </summary>
		void BossInitialize();

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="velo">弾ベクトル</param>
		void Update(const Vector3& velo);

		/// <summary>
		/// ボス出現
		/// </summary>
		void Pop();

		/// <summary>
		/// 攻撃
		/// </summary>
		void Attack();

		/// <summary>
		/// 移動
		/// </summary>
		void Move();

		/// <summary>
		/// 状態変化
		/// </summary>
		void ChangeState();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="viewProjection_">カメラ</param>
		void BossDraw(ViewProjection* viewProjection_);

		/// <summary>
		/// 死亡フラグ取得
		/// </summary>
		/// <returns></returns>
		bool GetIsDead() const { return isDead_; }

		/// <summary>
		/// 当たり判定
		/// </summary>
		/// <param name="info">衝突情報</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// ボス出現状態を取得
		/// </summary>
		/// <returns></returns>
		bool GetIsInvisible() { return isInvisible; }

		/// <summary>
		/// 透過度を取得
		/// </summary>
		/// <returns></returns>
		float GetAlpha() { return bossAlpha; }

		/// <summary>
		/// タイマーを取得
		/// </summary>
		/// <returns></returns>
		int GetTimer() { return appearTimer; }

		/// <summary>
		/// HPを取得
		/// </summary>
		/// <returns></returns>
		float GetHP() { return hp; }

		/// <summary>
		/// パーツ数を取得
		/// </summary>
		/// <returns></returns>
		int GetPartsNum() { return PARTS_NUM; }

		/// <summary>
		/// パーツを取得
		/// </summary>
		/// <param name="i">パーツ番号</param>
		/// <returns></returns>
		Object3d* GetParts(int i) { return parts[i]; }

		/// <summary>
		/// ボス登場演出をスキップ
		/// </summary>
		void SkipMovie();

		/// <summary>
		/// 倒された演出
		/// </summary>
		void SlainUpdate();

		/// <summary>
		/// 倒されたフラグ取得
		/// </summary>
		/// <returns></returns>
		bool GetISlained() { return isSlained; }



	private:

		static const int STATE_TIME = 125;
		static const int HIT_TIME_MAX = 10;
		static const int DAMAGE_NUM = 5;
		static const int SLAIN_TIME = 30;
		static const int POP_TIME_ONE = 35;
		static const int POP_TIME_TWO = 70;
		static const int POP_TIME_MAX = 150;
		static const int APPEAR_TIME = 75;
		static const float MAX_ALPHA;
		static const float ADD_ALPHA;
		static const float SHADOW_Y;
		static const float SHADOW_SCALE_AD;

	private:
		//デスフラグ
		bool isDead_ = false;
		bool isInvisible = true;
		//タイマー
		int appearTimer = 0;
		float bossAlpha = 0.0f;
		float hp;
		bool isHit;
		int hitTimer;
		int timeCount;
		int timer;

		//ボス行動情報
		enum State {
			WAIT,
			SHOT
		};
		State state;

		// モデル
		Model* bossModel = nullptr;
		Model* shadowModel = nullptr;
		//弾
		std::list<std::unique_ptr<MyEngine::BossBullet>> bullets_;
		static const int PARTS_NUM = 5;
		Object3d* parts[PARTS_NUM];
		Object3d* shadow = nullptr;
		Vector3 movePower = { 0.5f,0.5f,0.5f };
		Vector3 postmp;
		Vector3 bossSkipPos;
		Vector3 addVec;
		int slainTimer;
		bool isSlained;
	};
}
