#include "Player.h"
#include "string.h"
#include "RailCamera.h"
#include "SphereCollider.h"

//デストラクタ
Player::~Player() {
	delete playerModel;
}

//初期化
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize()) {
		return false;
	}

	Initialize();

	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("triangle_mat");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, 0));

	hp = 5;
	coolTime = 0;
	len = 6.0f;
	pTimer = 0;
	isHit = false;
	hitTime = 0;

	return true;
}

void Player::Update(Vector3 velo)
{
	input = Input::GetInstance();

	Move();
	Attack(velo);
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}
	//デスフラグの立った敵を削除
	bullets_.remove_if([](std::unique_ptr < PlayerBullet>& bullets_) {
		return bullets_->IsDead();
		});

	if (isHit == true) {
		hitTime++;
		if (hitTime == 15) {
			hitTime = 0;
			isHit = false;
		}
	}

	worldTransform_.UpdateMatrix();
	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };

	//player移動
	if (input->PushKey(DIK_W)) {
		if (input->PushKey(DIK_A) == true && input->PushKey(DIK_D) == false) {
			move = { -0.03f, 0.03f, 0 };
		}
		else if (input->PushKey(DIK_A) == false && input->PushKey(DIK_D) == true) {
			move = { 0.03f, 0.03f, 0 };
		}
		else {
			move = { 0, 0.04f, 0 };
		}
	}
	else if (input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { -0.03f, -0.03f, 0 };
		}
		else {
			move = { -0.04f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_D)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { 0.03f, -0.03f, 0 };
		}
		else {
			move = { 0.04f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_S)) {
		move = { 0, -0.04f, 0 };
	}

	//playerふわふわ
	if (pTimer < 75) {
		move += Vector3(0, 0.005f, 0);
	}
	else if (pTimer < 150) {
		move += Vector3(0, -0.005f, 0);
	}
	else {
		pTimer = 0;
	}

	Vector3 tmp = GetPosition() + move;
	//
	if (abs(tmp.x) <= 3.0f) {
		if (tmp.y >= -1.5f && tmp.y <= 2.0f) {
			SetPosition(GetPosition() + move);
		}
	}
	pTimer++;
}

void Player::Attack(Vector3 velo) {
	
	if (input->PushMouseLeft()) {
		if (coolTime == 0) {
			//弾を生成し初期化
		//複数
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();

			//単発
			newBullet->BulletInitialize(GetPosition(),velo);
			newBullet->SetCollider(new SphereCollider());

			//弾の登録
		   //複数
			newBullet->SetPosition(GetWorldPos());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));


			//クールタイムを設定
			coolTime = 8;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

	}
}

void Player::PlayerDraw(ViewProjection* viewProjection_) {
	if (hitTime % 5 == 0) {
		Draw(viewProjection_);
	}
	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class Enemy";
	const char* str2 = "class EnemyBullet";

	//相手がenemy
	if (strcmp(toCollisionName, str1) == 0) {
	}
	//相手がenemyの弾
	if (strcmp(toCollisionName, str2) == 0) {
		if (isHit == false) {
			hp--;
			isHit = true;
		}
	}
}