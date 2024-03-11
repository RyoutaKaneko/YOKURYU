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

namespace MyEngine {
	class Player : public Object3d
	{
	private:
		//体力状況
		enum Health {
			FINE,
			WEEKNESS,
			DYING,
			DIE
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
		void Update(const Vector3& vec, const std::vector<LockInfo>& info);

		/// <summary>
		/// 移動
		/// </summary>
		void Move();

		/// <summary>
		/// 翼の動き
		/// </summary>
		void WingMove();

		/// <summary>
		/// 攻撃
		/// </summary>
		/// <param name="velo">弾ベクトル</param>
		void Attack(const Vector3& velo);

		/// <summary>
		/// ロックオン攻撃
		/// </summary>
		/// <param name="info">ロックオン情報</param>
		void LockAttack(const std::vector<LockInfo>& info);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="viewProjection_"></param>
		void PlayerDraw(ViewProjection* viewProjection_);

		/// <summary>
		///  ゲームオーバー時の描画
		/// </summary>
		/// <param name="viewProjection_"></param>
		void DrawDead(ViewProjection* viewProjection_);

		/// <summary>
		/// レールに戻る
		/// </summary>
		void BackRail();

		/// <summary>
		/// 見た目のみの更新
		/// </summary>
		void ViewUpdate();

		/// <summary>
		/// 衝突時コールバック関数
		/// </summary>
		/// <param name="info">衝突情報</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// 死亡時
		/// </summary>
		void Dead();

		/// <summary>
		/// 方向ベクトル取得
		/// </summary>
		void GetVec(const Vector3& x_, const Vector3& y_);


		/////getter/////

		/// <summary>
		/// hp
		/// </summary>
		/// <returns></returns>
		float GetHP() { return hp; }

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
		/// 移動量
		/// </summary>
		/// <returns></returns>
		Vector3 GetMove() { return move; }

		/// <summary>
		/// 体力状況を取得
		/// </summary>
		/// <returns></returns>
		Health GetHealthState() { return healthState; }

		/// <summary>
		/// デスタイマーを取得
		/// </summary>
		/// <returns></returns>
		int GetDeathTimer() { return deathTimer; }

		/// <summary>
		/// 透過度を取得
		/// </summary>
		/// <returns></returns>
		float GetAlpha() { return alpha; }

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
		/// 状態を指定
		/// </summary>
		/// <param name="state"></param>
		void SetDie() { healthState = DIE; }

		/// <summary>
		/// 弾リストを取得
		/// </summary>
		/// <returns></returns>
		const std::list<std::unique_ptr<MyEngine::PlayerBullet>>& GetBullets() { return bullets_; }

		/// <summary>
		/// HPリセット
		/// </summary>
		void ResetHP();

		/// <summary>
		/// fang
		/// </summary>
		/// <returns></returns>
		Object3d* GetFang() { return fang; }

		/// <summary>
		/// eye
		/// </summary>
		/// <returns></returns>
		Object3d* GetEye() { return eye; }


	private:
		//定数
		static const int HP_MAX = 100;
		static const int ENERGY_MAX = 100;
		static const int ENEMY_DAMAGE = 10;
		static const int BOSS_DAMAGE = 25;
		static const int ADD_ENERGY = 5;
		static const int COOLTIME_MAX = 6;
		static const int WEEKNESS_NUM = 75;
		static const int DYING_NUM = 25;
		static const int DIE_NUM = 0;
		static const int HITTIME_MAX = 15;
		static const int ALPHA_MAX = 1;
		static const int FLOAT_TIME_MID = 75;
		static const int FLOAT_TIME_END = 150;
		static const int ULT_TIME_MID = 50;
		static const int ULT_TIME_END = 175;
		static const int DEATH_TIME_ONE = 25;
		static const int DEATH_TIME_TWO = 50;
		static const int DEATH_TIME_THREE = 100;
		static const int HIT_TIME = 3;
		static const int WING_ROTATE_MAX = 45;
		static const int WING_ROTATE_MIN = 10;
		static const float ADD_ALPHA;
		static const float SLANTING_POWER;
		static const float FLOAT_POWER;
		static const float MOVE_POWER;
		static const float ADD_Y_VEC;
		static const float SUB_Y_VEC;
		static const float CAMERA_LEN_X;
		static const float CAMERA_LEN_Y_MAX;
		static const float CAMERA_LEN_Y_MIN;
		static const float CAMERA_LEN_Z;

	private:
		Input* input = nullptr;

		//obj
		Object3d* fang = nullptr;
		Object3d* eye = nullptr;
		Object3d* wingR = nullptr;
		Object3d* wingL = nullptr;
		// モデル
		Model* playerModel = nullptr;
		Model* fangModel = nullptr;
		Model* eyeModel = nullptr;
		Model* wingRModel = nullptr;
		Model* wingLModel = nullptr;
		//パーティクル
		Particle* particle = nullptr;
		//弾 
		std::list<std::unique_ptr<MyEngine::PlayerBullet>> bullets_;
		//HP
		float hp;
		int coolTime = 0;
		int lockCool = 0;
		float len = 6;
		int pTimer = 0;
		bool isHit;
		bool isShooted;
		int hitTime;
		float alpha;
		Vector3 pos_;
		Vector3 rot_;
		Vector3 move;
		Vector3 dMove;
		Vector3 leftVec;
		Vector3 rightVec;
		Health healthState;
		Vector3 addCameraLen;
		int deathTimer;
		float wingRRotate;
		float wingLRotate;
		bool shotRight;
	};
}
