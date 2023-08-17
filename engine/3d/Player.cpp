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
	/*playerModel = Model::LoadFromOBJ("triangle_mat");*/
	playerModel = Model::LoadFromOBJ("box");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, 500));
	SetRotation(Vector3(0, 270, 0));

	hp = 100;
	coolTime = 0;
	len = 6.0f;
	pTimer = 0;
	isHit = false;
	isShooted = false;
	hitTime = 0;
	alpha = 1.0f;

	return true;
}

void Player::Update(Vector3 velo, std::vector<LockInfo>& info)
{
	input = Input::GetInstance();
	if (isShooted == true) {
		isShooted = false;
	}


	Move();
	LockAttack(info);
	Attack(velo);
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		if (bullet->GetIsHoming() == true) {
			bullet->HomingVec(GetWorldPos());
		}
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
	if (alpha < 1.0f) {
		alpha += 0.01f;
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
			if (GetPosition().z < -1.6f) {
				move.z += 0.05f;
			}
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
			newBullet->BulletInitialize(velo + Vector3(0,0.05f,0));
			newBullet->SetCollider(new SphereCollider());

			//弾の登録
		   //複数
			newBullet->SetPosition(GetWorldPos());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));


			//クールタイムを設定
			coolTime = 6;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

	}
}

void Player::LockAttack(std::vector<LockInfo>& info)
{
	if (input->GetInstance()->TriggerMouseRight()) {
		for (int i = 0; i < info.size(); i++) {
			//弾を生成し初期化
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			Vector3 shotVec = (info[i].vec - GetWorldPos());
			//単発
			newBullet->BulletInitialize(shotVec);
			newBullet->SetCollider(new SphereCollider());

			//弾の登録
		   //複数
			newBullet->SetPosition(GetWorldPos());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			newBullet->SetLock(info[i].obj);
			newBullet->SetisHoming(true);
			bullets_.push_back(std::move(newBullet));
		}
		isShooted = true;
	}
}

void Player::PlayerDraw(ViewProjection* viewProjection_) {
	if (hitTime % 5 == 0) {
		Draw(viewProjection_,alpha);
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
	const char* str3 = "class BossBullet";

	//相手がenemy
	if (strcmp(toCollisionName, str1) == 0) {
	}
	//相手がenemyの弾
	if (strcmp(toCollisionName, str2) == 0) {
		if (isHit == false) {
			hp-=10;
			isHit = true;
		}
	}
	//相手がbossの弾
	if (strcmp(toCollisionName, str3) == 0) {
		if (isHit == false) {
			hp-=25;
			isHit = true;
		}
	}
}