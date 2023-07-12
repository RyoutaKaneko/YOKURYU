#include "EnemyBullet.h"
#include "BaseCollider.h"

void EnemyBullet::BulletInitialize(const Vector3& position) {

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

void EnemyBullet::Update(const Vector3& playerPos_) {
	if (bulletTime < 20) {
		velocity = (playerPos_ - GetPosition()) * 0.02f;
		bulletTime++;
	}

	SetPosition(GetPosition() + velocity);

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

void EnemyBullet::OnCollision(const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class Player";

	//相手がenemy
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}
