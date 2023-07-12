#include "PlayerBullet.h"
#include "BaseCollider.h"

void PlayerBullet::BulletInitialize(const Vector3& position, const Vector3& velocity) {

	Initialize();

	// OBJからモデルデータを読み込む
	bulletModel = Model::LoadFromOBJ("ironSphere");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(bulletModel);

	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update() {
	SetPosition(GetPosition() + velocity_);

	worldTransform_.UpdateMatrix();

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

void PlayerBullet::OnCollision(const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class Enemy";
	const char* str2 = "class EnemyBullet";

	//相手がenemy
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}

	//相手がenemyの弾
	if (strcmp(toCollisionName, str2) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}
