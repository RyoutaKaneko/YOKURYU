#include "Enemy.h"
#include "string.h"

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

	worldTransform_.UpdateMatrix();
	timer++;
}

//void Enemy::OnCollision(const CollisionInfo& info)
//{
//	const char* str1 = "class Player";
//
//	//相手がplayer
//	if (strcmp(toCollisionName, str1) == 0) {
//		isDead_ = true;
//	}
//}
//
//void Enemy::OffCollision(const CollisionInfo& info)
//{
//
//}