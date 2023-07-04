#include "Enemy.h"
#include "string.h"
#include "BaseCollider.h"

//デストラクタ
Enemy::~Enemy() {
	delete enemyModel;
}

//初期化
void Enemy::EnemyInitialize()
{
	Initialize();
	// OBJからモデルデータを読み込む
	enemyModel = Model::LoadFromOBJ("triangle_mat");
	enemyModel->LoadTexture("Resources/red.png");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(enemyModel);
	/*SetCollider(new SphereCollider);*/
	isDead_ = false;
	timer = 0;
}

void Enemy::Update() {
	if (timer < 75) {
		SetPosition(GetPosition() + Vector3( 0, 0.005f, 0 ));
	}
	else if (timer < 150) {
		SetPosition(GetPosition() + Vector3(0, -0.005f, 0));
	}
	else {
		timer = 0;
	}
	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
	worldTransform_.UpdateMatrix();
	timer++;
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class PlayerBullet";

	//相手がplayerの弾
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}