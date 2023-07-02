#include "PlayerBullet.h"

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
	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void PlayerBullet::OnCollision() {
	//デスフラグ
	isDead_ = true;
}
