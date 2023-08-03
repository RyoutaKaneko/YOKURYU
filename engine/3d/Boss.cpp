#include "Boss.h"
#include "SphereCollider.h"

Boss::~Boss()
{
	delete bossModel;
}

void Boss::BossInitialize()
{
	Initialize();
	// OBJからモデルデータを読み込む
	bossModel = Model::LoadFromOBJ("fighter");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(bossModel);
	SetPosition({ 0,15,-200 });
	SetScale({ 10,10,10 });
	isDead_ = false;
	isInvisible = true;
	//タイマー
	appearTimer = 0;
	bossAlpha = 0.0f;
	hp = 30;
	isHit = false;
	hitTimer = 0;
	timer = 0;
	timeCount = 0;
}

void Boss::Update()
{
	if (appearTimer > 0) {
		if (appearTimer > 150) {
			SetPosition(GetPosition() + Vector3(0.5f, -0.1f, 0));
		}
		if (appearTimer > 100) {
			bossAlpha += 0.02f;
		}
		appearTimer--;
	}
	//ボス登場後
	if(isInvisible == false) {
		float moveX = 0;
		if (timeCount == 0) {
			moveX = -0.05f;
		}
		else if (timeCount == 1) {
			moveX = 0.05f;
		}
		else if (timeCount == 2) {
			moveX = 0.05f;
		}
		else if(timeCount == 3){
			moveX = -0.05f;
		}

		if (timer < 75) {
			SetPosition(GetPosition() + Vector3(moveX, 0.01f, 0));
		}
		else if (timer < 150) {
			SetPosition(GetPosition() + Vector3(moveX, -0.01f, 0));
		}
		else {
			timer = 0;
			timeCount++;
			if (timeCount == 4) {
				timeCount = 0;
			}
		}
		timer++;
	}
	if (hitTimer > 0) {
		hitTimer--;
		if (hitTimer == 0) {
			isHit = false;
		}
	}
	if (hp == 0) {
		isDead_ = true;
	}
	worldTransform_.UpdateMatrix();
	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}

void Boss::Pop()
{
	if (isInvisible == true) {
		isInvisible = false;
	}
	appearTimer = 300;

}

void Boss::OnCollision(const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class PlayerBullet";

	//相手がplayerの弾
	if (strcmp(toCollisionName, str1) == 0) {
		if (isHit == false && isInvisible == false) {
			isHit = true;
			hitTimer = 30;
			hp--;
		}
	}
}
