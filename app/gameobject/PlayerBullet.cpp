/**
 * @file PlayerBullet.h
 * @brief プレイヤーの攻撃に使う弾リスト用クラス
 * @author カネコ_リョウタ
 */

#include "PlayerBullet.h"
#include "BaseCollider.h"

const float MyEngine::PlayerBullet::correction = 0.25f;

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
}

void MyEngine::PlayerBullet::Update() {

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
		velocity_ = lockObj->GetWorldPos() - GetPosition();
		velocity_ = velocity_ * correction;
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
		if (isDead_ == false) {
			isDead_ = true;
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
		if (isDead_ == false) {
			isDead_ = true;
		}
	}

}