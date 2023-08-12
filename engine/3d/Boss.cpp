#include "Boss.h"
#include "SphereCollider.h"
#include "time.h"
#include "stdlib.h"

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
	SetPosition({ -75,65,-200 });
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
	state = WAIT;
	//乱数
	srand(time(NULL));
}

void Boss::Update(Vector3 velo)
{
	//登場時
	if (appearTimer > 0) {
		if (appearTimer > 150) {
			SetPosition(GetPosition() + Vector3(0.5f, -0.1f, 0));
		}
		if (appearTimer > 100) {
			bossAlpha += 0.02f;
		}
		appearTimer--;
	}
	//基本挙動
	ChangeState();
	Move();

	//弾があるなら更新
	for (std::unique_ptr<BossBullet>& bullet : bullets_) {
		bullet->Update(velo);
	}
	//デスフラグの立った敵を削除
	bullets_.remove_if([](std::unique_ptr <BossBullet>& bullets_) {
		return bullets_->IsDead();
		});
	
	 //ダメージ判定
	if (hitTimer > 0) {
		hitTimer--;
		if (hitTimer == 0) {
			isHit = false;
		}
	}
	//HPが0なら死亡
	if (hp == 0) {
		isDead_ = true;
	}
	//更新
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

void Boss::Attack()
{
	//弾を生成し初期化
//複数
	std::unique_ptr<BossBullet> newBullet = std::make_unique<BossBullet>();

	//単発													   
	newBullet->BulletInitialize(GetPosition());
	newBullet->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.5f));

	//弾の登録										 
   //複数
	newBullet->SetPosition(GetPosition());
	newBullet->SetScale({ 0.4f,0.4f,0.4f });
	bullets_.push_back(std::move(newBullet));
}

void Boss::Move()
{
	//ボス登場後
	if (isInvisible == false) {
		float moveX = 0;
		if (timeCount == 0) {
			moveX = -0.025f;
		}
		else if (timeCount == 1) {
			moveX = 0.025f;
		}
		else if (timeCount == 2) {
			moveX = 0.025f;
		}
		else if (timeCount == 3) {
			moveX = -0.025f;
		}

		if (timer < 75) {
			SetPosition(GetPosition() + Vector3(0.0f, 0.01f, 0.0f));
		}
		else if (timer < 150) {
			SetPosition(GetPosition() + Vector3(0.0f, -0.01f, 0.0f));
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
}

void Boss::ChangeState()
{
	//待機状態
	if (state == WAIT) {
		//乱数により行動を決定
		int random = rand() % 2 + 1;
		//結果を見て状態を遷移
		if (random == 1) {
			state = SHOT;
		}
		else {
			state = SHOT;
		}
	}
	//射撃状態
	else if (state == SHOT) {

	}
}

void Boss::BossDraw(ViewProjection* viewProjection_)
{
	Draw(viewProjection_, bossAlpha);
	//弾描画
	for (std::unique_ptr<BossBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
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
