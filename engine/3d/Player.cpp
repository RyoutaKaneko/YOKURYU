#include "Player.h"
#include "string.h"
#include "RailCamera.h"

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

	hp = 3;
	coolTime = 0;
	len = 6.0f;
	pTimer = 0;

	return true;
}

void Player::Update(Vector3 cameraPos,Vector3 velo)
{
	input = Input::GetInstance();

	Move();
	Attack(cameraPos,velo);
	//デスフラグの立った敵を削除
	bullets_.remove_if([](std::unique_ptr < PlayerBullet>& bullets_) {
		return bullets_->IsDead();
		});
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		if (bullet->IsDead() == false) {
			bullet->Update();
		}
	}
	//playerふわふわ
	if (pTimer < 75) {
		SetPosition(GetPosition() + Vector3(0, 0.005f, 0));
	}
	else if (pTimer < 150) {
		SetPosition(GetPosition() + Vector3(0, -0.005f, 0));
	}
	else {
		pTimer = 0;
	}

	worldTransform_.UpdateMatrix();
	pTimer++;
}

void Player::Move()
{
	Vector3 move = { 0,0,0 };

	//player移動
	if (input->PushKey(DIK_W)) {
		if (input->PushKey(DIK_A) == true && input->PushKey(DIK_D) == false) {
			move = { -0.02f, 0.02f, 0 };
		}
		else if (input->PushKey(DIK_A) == false && input->PushKey(DIK_D) == true) {
			move = { 0.02f, 0.02f, 0 };
		}
		else {
			move = { 0, 0.03f, 0 };
		}
	}
	else if (input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { -0.02f, -0.02f, 0 };
		}
		else {
			move = { -0.03f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_D)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { 0.02f, -0.02f, 0 };
		}
		else {
			move = { 0.03f, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_S)) {
		move = { 0, -0.03f, 0 };
	}

	Vector3 tmp = GetPosition() + move;
	//
	if (abs(tmp.x) <= 3.5f) {
		if (abs(tmp.y) <= 2.0f) {
			SetPosition(GetPosition() + move);
		}
	}
}

void Player::Attack(Vector3 cameraPos ,Vector3 velo) {
	
	if (input->PushKey(DIK_SPACE)) {
		if (coolTime == 0) {
			//弾を生成し初期化
		//複数
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();

			//単発
			/*PlayerBullet* newBullet = new PlayerBullet();*/
			newBullet->BulletInitialize(GetPosition(),velo);

			//弾の登録										 
		   //複数
			newBullet->SetPosition(cameraPos + Vector3{-worldTransform_.position_.x * 1.5f,worldTransform_.position_.y,worldTransform_.position_.z });
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));

			//単発
			/*bullet_.reset(newBullet);*/

			//クールタイムを設定
			coolTime = 10;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

	}
}

void Player::PlayerDraw(ViewProjection* viewProjection_) {
	Draw(viewProjection_);
	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		if (bullet->IsDead() == false) {
			bullet->Draw(viewProjection_);
		}
	}
}