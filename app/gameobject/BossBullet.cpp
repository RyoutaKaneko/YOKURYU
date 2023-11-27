/**
 * @file BossBullet.h
 * @brief ボス攻撃に使う弾リスト用クラス
 * @author カネコ_リョウタ
 */

#include "BossBullet.h"
#include "BaseCollider.h"

void BossBullet::BulletInitialize()
{
	Initialize();

	// OBJからモデルデータを読み込む
	bulletModel = Model::LoadFromOBJ("bossBullet");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(bulletModel);

	//体力指定
	hp = 3;
	hitTime = 0;
	isHit = false;
}

void BossBullet::Update(const Vector3& playerPos_)
{
	//移動ベクトルを計算
	velocity = playerPos_ - GetPosition();
	velocity.normalize();
	//座標を加算
	SetPosition(GetPosition() + (velocity * 0.5f));
	//更新
	GetWorldTransform().UpdateMatrix();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
	//ヒット時クールタイム
	if (hitTime > 0) {
		hitTime--;
		if (isHit == false) {
			isHit = true;
			bulletModel->LoadTexture("Resources/bossBullet/stonedmg.png");
		}
	}
	else {
		if (isHit == true) {
			isHit = false;
			if (hp == 2) {
				bulletModel->LoadTexture("Resources/bossBullet/stone3.png");
			}
			else if (hp == 1) {
				bulletModel->LoadTexture("Resources/bossBullet/stone3.png");
			}
		}
	}
	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void BossBullet::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class Player";
	const char* str2 = "class PlayerBullet";

	//相手がplayer
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
	//相手がplayerの弾
	if (strcmp(GetToCollName(), str2) == 0) {
		if (hitTime == 0) {
			if (hp <= 0) {
				isDead_ = true;
			}
			else {
				hp--;
				hitTime = 10;
			}
		}
	}
}
