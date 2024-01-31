/**
 * @file EnemyBullet.h
 * @brief 通常敵攻撃に使う弾リスト用クラス
 * @author カネコ_リョウタ
 */

#include "EnemyBullet.h"
#include "BaseCollider.h"

void MyEngine::EnemyBullet::BulletInitialize() {

	Initialize();

	// OBJからモデルデータを読み込む
	bulletModel = Model::LoadFromOBJ("triangle_mat");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(bulletModel);

	//引数で受け取った速度をメンバ変数に代入
	bulletTime = 0;
}

void MyEngine::EnemyBullet::Update(const Vector3& playerPos_,bool isDead) {

	if (bulletTime < HOMING_TIME) {
		velocity = (playerPos_ - GetPosition());
		velocity.normalize();
		bulletTime++;
	}

	SetPosition(GetPosition() + velocity);

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
	//弾を撃った敵が死んでいたら弾も消す
	if (isDead == true) {
		isDead_ = true;
	}
}

void MyEngine::EnemyBullet::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class MyEngine::Player";
	const char* str2 = "class MyEngine::PlayerBullet";

	//相手がplayer
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
	//相手がplayerの弾
	if (strcmp(GetToCollName(), str2) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}
