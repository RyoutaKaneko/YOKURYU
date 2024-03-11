/**
 * @file PlayerBullet.h
 * @brief プレイヤーの攻撃に使う弾リスト用クラス
 * @author カネコ_リョウタ
 */

#include "PlayerBullet.h"
#include "BaseCollider.h"

const float MyEngine::PlayerBullet::correction = 0.0001f;
const float MyEngine::PlayerBullet::ADD_ACCEL = 0.2f;
const int MyEngine::PlayerBullet::HOMING_TIME = 5;

void MyEngine::PlayerBullet::BulletInitialize(const Vector3& velocity) {

	Initialize();

	// OBJからモデルデータを読み込む
	bulletModel = Model::LoadFromOBJ("bullet");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(bulletModel);
	SetScale({ 3.0,3.0,3.0 });

	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	homingTime = 0;
	accel = 1.4f;
}

void MyEngine::PlayerBullet::Update() {

	//更新
	SetPosition(GetPosition() + velocity_);

	GetWorldTransform().UpdateMatrix();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void MyEngine::PlayerBullet::HomingVec()
{
	//ロックオン先に飛んでいく
	if (isHoming == true) {
		if (homingTime < HOMING_TIME) {
			homingTime++;
			if (homingTime == HOMING_TIME) {
				lockPos = GetWorldPos();
			}
		}
		else if(homingTime >= HOMING_TIME) {
			//v1,v2を求める
			Vector3 toPlayer = lockObj->GetWorldPos() - GetPosition();
			toPlayer = toPlayer.normalize();
			velocity_ = velocity_.normalize();
			float t = 0.5f;
			//球面線形補完する
			velocity_ = Vector3::Slerp(velocity_, toPlayer, t) * accel;
		}
	}
}

void MyEngine::PlayerBullet::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class MyEngine::Enemy";
	const char* str2 = "class MyEngine::Boss";
	const char* str3 = "class MyEngine::BossBullet";

	//相手がenemy
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isHoming == false) {
			if (isDead_ == false) {
				isDead_ = true;
			}
		}
		else {
			if (info.object == lockObj) {
				if (isDead_ == false) {
					isDead_ = true;
				}
			}
		}
	}

	//相手がボス
	if (strcmp(GetToCollName(), str2) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
	//相手がボスの弾
	if (strcmp(GetToCollName(), str3) == 0) {
		if (isHoming == false) {
			if (isDead_ == false) {
				isDead_ = true;
			}
		}
	}
}