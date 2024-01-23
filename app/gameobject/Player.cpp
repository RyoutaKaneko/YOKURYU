/**
 * @file Player.h
 * @brief プレイヤーの移動、攻撃、描画をまとめたクラス
 * @author カネコ_リョウタ
 */

#include "Player.h"
#include "string.h"
#include "RailCamera.h"
#include "SphereCollider.h"
#include"Input.h"

const float Player::ADD_ALPHA = 0.02f;
const float Player::SLANTING_POWER = 0.03f;
const float Player::FLOAT_POWER = 0.005f;
const float Player::MOVE_POWER = 0.08f;
const float Player::ADD_Y_VEC = 0.03f;
const float Player::SUB_Y_VEC = -0.3f;
const float Player::CAMERA_LEN_X = 2.5f;
const float Player::CAMERA_LEN_Y_MAX = 2.0f;
const float Player::CAMERA_LEN_Y_MIN = -1.5f;
const float Player::CAMERA_LEN_Z = -1.6f;

//デストラクタ
Player::~Player() {
	delete playerModel;
}

//初期化
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize()) {
		return false;
	}

	input = Input::GetInstance();
	Initialize();

	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("dragonbody");
	fangModel = Model::LoadFromOBJ("dragonbite");
	eyeModel = Model::LoadFromOBJ("dragoneye");
	wingRModel = Model::LoadFromOBJ("wingR");
	wingLModel = Model::LoadFromOBJ("wingL");
	// 3Dオブジェクト生成
	Create();
	fang = new Object3d();
	fang->Initialize();
	fang = Object3d::Create();
	eye = new Object3d();
	eye->Initialize();
	eye = Object3d::Create();
	wingR = new Object3d();
	wingR->Initialize();
	wingR = Object3d::Create();
	wingL = new Object3d();
	wingL->Initialize();
	wingL = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, 500));
	SetRotation(Vector3(0, 270, 0));
	SetScale({ 1.5f, 1.5f, 1.5f });
	fang->SetModel(fangModel);
	fang->GetWorldTransform().SetParent3d(&GetWorldTransform());
	eye->SetModel(eyeModel);
	eye->GetWorldTransform().SetParent3d(&GetWorldTransform());
	wingR->SetModel(wingRModel);
	wingR->GetWorldTransform().SetParent3d(&GetWorldTransform());
	wingR->SetPosition({-0.5f,-0.2f,0});
	wingL->SetModel(wingLModel);
	wingL->GetWorldTransform().SetParent3d(&GetWorldTransform());
	wingL->SetPosition({-0.5f,-0.2f,0.2f});

	hp = HP_MAX;
	coolTime = 0;
	len = 6.0f;
	pTimer = 0;
	isHit = false;
	isShooted = false;
	hitTime = 0;
	alpha = 1.0f;
	energy = 0;
	pos_ = { 0,0,0 };
	rot_ = { 0,0,0 };
	healthState = FINE;
	deathTimer = 0;
	dMove = { 0,0,0 };
	wingRRotate = -2.0f;
	wingLRotate = 2.0f;
	addCameraLen = { 0,0,0.1f };

	return true;
}

void Player::Update(Vector3 vec, std::vector<LockInfo>& info)
{
	if (isShooted == true) {
		isShooted = false;
	}


	Move();
	LockAttack(info);
	Attack(vec);
	//player弾
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		if (bullet->GetIsHoming() == true) {
			bullet->HomingVec();
		}
		bullet->Update();
	}
	//デスフラグの立った敵を削除
	bullets_.remove_if([](std::unique_ptr < PlayerBullet>& bullets_) {
		return bullets_->IsDead();
		});

	//被弾時処理
	if (isHit == true) {
		hitTime++;
		if (hitTime == HITTIME_MAX) {
			hitTime = 0;
			isHit = false;
		}
		//6割りでhp表示変化
		if (hp <= WEEKNESS_NUM && healthState == FINE) {
			healthState = WEEKNESS;
		}
		//4/1で瀕死
		else if (hp <= DYING_NUM && healthState == WEEKNESS) {
			healthState = DYING;
		}
		else if (hp <= DIE_NUM && healthState == DYING) {
			healthState = DIE;
		}
	}
	WingMove();

	//更新
	GetWorldTransform().UpdateMatrix();
	fang->Update();
	eye->Update();
	wingR->Update();
	wingL->Update();
	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
	if (alpha < ALPHA_MAX) {
		alpha += ADD_ALPHA;
	}
}

void Player::Move()
{
	move = { 0,0,0 };

	//player移動
	if (input->PushKey(DIK_W)) {
		if (input->PushKey(DIK_A) == true && input->PushKey(DIK_D) == false) {
			move = { -SLANTING_POWER, SLANTING_POWER, 0 };
		}
		else if (input->PushKey(DIK_A) == false && input->PushKey(DIK_D) == true) {
			move = { SLANTING_POWER, SLANTING_POWER, 0 };
		}
		else {
			move = { 0, MOVE_POWER, 0 };
		}
	}
	else if (input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { -SLANTING_POWER, -SLANTING_POWER, 0 };
		}
		else {
			move = { -MOVE_POWER, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_D)) {
		if (input->PushKey(DIK_S) == true && input->PushKey(DIK_W) == false) {
			move = { SLANTING_POWER, -SLANTING_POWER, 0 };
		}
		else {
			move = { MOVE_POWER, 0, 0 };
		}
	}
	else if (input->PushKey(DIK_S)) {
		move = { 0, -MOVE_POWER, 0 };
	}

	Vector3 floating(0, 0, 0);
	//playerふわふわ
	if (pTimer < FLOAT_TIME_MID) {
		floating += Vector3(0, FLOAT_POWER, 0);
	}
	else if (pTimer < FLOAT_TIME_END) {
		floating += Vector3(0, -FLOAT_POWER, 0);
	}
	else {
		pTimer = 0;
	}

	//カメラとの距離感調整
	Vector3 tmp = GetPosition() + move + floating;
	if (abs(tmp.x) <= CAMERA_LEN_X) {
		if (tmp.y >= CAMERA_LEN_Y_MIN && tmp.y <= CAMERA_LEN_Y_MAX) {
			if (GetPosition().z < CAMERA_LEN_Z) {
				SetPosition(GetPosition() + move + floating + addCameraLen);
			}
			else {
				SetPosition(GetPosition() + move + floating);
			}
		}
		else {
			move = { 0,0,0 };
		}
	}
	else {
		move = { 0,0,0 };
	}
	pTimer++;
}

void Player::WingMove()
{
	//羽の動き
	if (wingR->GetRotation().x < -WING_ROTATE_MAX) {
		wingRRotate *= -1;
	}
	else if (wingR->GetRotation().x > WING_ROTATE_MIN) {
		wingRRotate *= -1;
	}

	if (wingL->GetRotation().x > WING_ROTATE_MAX) {
		wingLRotate *= -1;
	}
	else if (wingL->GetRotation().x < -WING_ROTATE_MIN) {
		wingLRotate *= -1;
	}

	wingR->SetRotation(wingR->GetRotation() + Vector3(wingRRotate, 0, 0));
	wingL->SetRotation(wingL->GetRotation() + Vector3(wingLRotate, 0, 0));
}

void Player::Attack(Vector3 velo) {
	
	if (Input::GetInstance()->PushMouseLeft()) {
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
			coolTime = COOLTIME_MAX;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

	}
}

void Player::LockAttack(std::vector<LockInfo>& info)
{
	if (Input::GetInstance()->LeftMouseRight() == true) {
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
	if (hitTime % HIT_TIME == 0) {
		Draw(viewProjection_,alpha);
		wingR->Draw(viewProjection_, alpha);
		wingL->Draw(viewProjection_, alpha);
		fang->Draw(viewProjection_, alpha);
		eye->Draw(viewProjection_, alpha);
	}
	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}

void Player::DrawDead(ViewProjection* viewProjection_)
{
	Draw(viewProjection_);
	fang->Draw(viewProjection_);
	wingR->Draw(viewProjection_);
	wingL->Draw(viewProjection_);
}

void Player::BackRail()
{
	SetPosition(pos_);
	SetRotation(rot_);
}

void Player::ViewUpdate()
{
	if (healthState != DIE) {
		WingMove();
	}
	GetWorldTransform().UpdateMatrix();
	fang->Update();
	eye->Update();
	wingR->Update();
	wingL->Update();
}

void Player::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class EnemyBullet";
	const char* str2 = "class BossBullet";
	//相手がenemyの弾
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isHit == false) {
			hp-=ENEMY_DAMAGE;
			isHit = true;
		}
	}
	//相手がbossの弾
	if (strcmp(GetToCollName(), str2) == 0) {
		if (isHit == false) {
			hp-=BOSS_DAMAGE;
			isHit = true;
		}
	}
}

void Player::Dead()
{
	Vector3 addVelo = { 0.0f,0.0f,0.0f };

	if (isHit == true) {
		hitTime++;
		if (hitTime == HITTIME_MAX) {
			hitTime = 0;
			isHit = false;
		}
		//6割りでhp表示変化
		if (hp <= WEEKNESS_NUM && healthState == FINE) {
			healthState = WEEKNESS;
		}
		//4/1で瀕死
		else if (hp<= DYING_NUM && healthState == WEEKNESS) {
			healthState = DYING;
		}
		else if (hp <= DIE_NUM && healthState == DYING) {
			healthState = DIE;
		}
	}

	if (deathTimer < DEATH_TIME_ONE) {}
	else if (deathTimer < DEATH_TIME_TWO) {
		addVelo = { 0.0f,ADD_Y_VEC,0.0f };
		dMove = addVelo;
		SetPosition(GetPosition() + dMove);
	}
	else if (deathTimer < DEATH_TIME_THREE) {
		addVelo = { 0.0f,SUB_Y_VEC,0.0f };
		dMove = addVelo;
		SetPosition(GetPosition() + dMove);
	}
	//更新
	deathTimer++;
	GetWorldTransform().UpdateMatrix();
	fang->Update();
	eye->Update();
	wingR->Update();
	wingL->Update();
}

void Player::ResetHP() {
	hp = HP_MAX;
	healthState = FINE;
}