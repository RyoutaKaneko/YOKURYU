/**
 * @file Boss.h
 * @brief ボス全般(ステータス、行動、描画)をまとめたもの
 * @author カネコ_リョウタ
 */


#include "Boss.h"
#include "SphereCollider.h"
#include "time.h"
#include "stdlib.h"
#include "GameScene.h"

const float MyEngine::Boss::MAX_ALPHA = 1.0f;
const float MyEngine::Boss::ADD_ALPHA = 0.04f;
const float MyEngine::Boss::SHADOW_Y = 4.92f;
const float MyEngine::Boss::SHADOW_SCALE_AD = 22.0f;

MyEngine::Boss::~Boss()
{
	delete bossModel;
	delete shadow;
	delete shadowModel;
}

void MyEngine::Boss::BossInitialize()
{
	Initialize();
	shadow = new Object3d;
	shadow->Initialize();
	// OBJからモデルデータを読み込む
	bossModel = Model::LoadFromOBJ("fighter");
	shadowModel = Model::LoadFromOBJ("panel");
	shadowModel->LoadTexture("Resources/shadow.png");
	// 3Dオブジェクト生成
	Create();
	shadow->Create();
	// オブジェクトにモデルをひも付ける
	SetModel(bossModel);
	shadow->SetModel(shadowModel);
	shadow->SetRotation({ 0,0,90 });
	shadow->SetScale({ 20,20,20 });
	SetPosition({ -75,65,-200 });
	SetScale({ 10,10,10 });
	//パーツの初期化
	for (int i = 0; i < PARTS_NUM; i++) {
		parts[i] = Create();
		parts[i]->GetWorldTransform().SetParent3d(&GetWorldTransform());
		parts[i]->SetCollider(new SphereCollider());
	}
	parts[0]->SetPosition({ -2.0f,0.0f,-0.5f });
	parts[1]->SetPosition({ 2.0f,0.0f,-0.5f });
	parts[2]->SetPosition({ 0.0f,0.0f,1.0f });
	parts[3]->SetPosition({ -3.0f,0.0f,-1.0f });
	parts[4]->SetPosition({ 3.0f,0.0f,-1.0f });

	isDead_ = false;
	isInvisible = true;
	//タイマー
	appearTimer = 0;
	bossAlpha = 0.0f;
	hp = 300;
	isHit = false;
	hitTimer = 0;
	timer = 0;
	timeCount = 0;
	state = WAIT;
	slainTimer = 0;
	isSlained = false;
	bossSkipPos = { 0.0f,49.99f,-200.0f };
	addVec = { 0.0f,0.01f,0.0f };
	//乱数
	srand((unsigned int)time(NULL));
}

void MyEngine::Boss::Update(const Vector3& velo)
{
	//登場時
	if (appearTimer >= 0) {
		if (appearTimer > APPEAR_TIME) {
			Vector3 velocity = { 1.0f, -0.2f, 0 };
			SetPosition(GetPosition() + velocity);
		}
		if (bossAlpha < MAX_ALPHA) {
			bossAlpha += ADD_ALPHA;
		}
		appearTimer--;
	}
	//基本挙動
	Move();
	if (appearTimer < 0) {
		ChangeState();
	}

	//弾があるなら更新
	for (std::unique_ptr<MyEngine::BossBullet>& bullet : bullets_) {
		bullet->Update(velo);
	}
	//デスフラグの立った敵を削除
	bullets_.remove_if([](std::unique_ptr <MyEngine::BossBullet>& bullets_) {
		return bullets_->IsDead();
		});
	
	 //ダメージ判定
	if (hitTimer > 0) {
		SetPosition(GetPosition() + movePower);
		movePower *= -1;
		hitTimer--;
		if (hitTimer == 0) {
			isHit = false;
		}
	}
	//HPが0なら死亡
	if (hp <= 0) {
		isDead_ = true;
	}
	//影
	Vector3 spos = GetPosition();
	shadow->SetPosition({ spos.x + SHADOW_SCALE_AD,SHADOW_Y,spos.z - SHADOW_SCALE_AD });
	shadow->Update();

	//更新
	GetWorldTransform().UpdateMatrix();
	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
	//ボスパーツアップデート
	for (int i = 0; i < PARTS_NUM; i++) {
		parts[i]->Update();
	}
}

void MyEngine::Boss::Pop()
{
	if (isInvisible == true) {
		isInvisible = false;
	}
	appearTimer = POP_TIME_MAX;
}

void MyEngine::Boss::Attack()
{
	//弾を生成し初期化
	std::unique_ptr<MyEngine::BossBullet> newBullet = std::make_unique<MyEngine::BossBullet>();

	//単発													   
	newBullet->BulletInitialize();
	newBullet->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 5.0f));

	//弾の登録										 
   //複数
	newBullet->SetPosition(GetPosition());
	newBullet->SetScale({ 1.2f,1.2f,1.2f });
	bullets_.push_back(std::move(newBullet));
}

void MyEngine::Boss::Move()
{
	//ボス登場後
	if (isInvisible == false) {
		if (timer < POP_TIME_ONE) {
			SetPosition(GetPosition() + addVec);
		}
		else if (timer < POP_TIME_TWO) {
			SetPosition(GetPosition() + (addVec * -1));
		}
		else {
			timer = 0;
		}
		timer++;
	}
}

void MyEngine::Boss::ChangeState()
{
	//待機状態
	if (state == WAIT) {
		if (timeCount >= STATE_TIME) {
			state = SHOT;
			timeCount = 0;
		}	
		else {
			timeCount++;
		}
	}
	//射撃状態
	else if (state == SHOT) {
		Attack();
		state = WAIT;
	}
}

void MyEngine::Boss::BossDraw(ViewProjection* viewProjection_)
{
	Draw(viewProjection_, bossAlpha);
	shadow->Draw(viewProjection_, bossAlpha);
	//弾描画
	if (isSlained == false) {
		for (std::unique_ptr<MyEngine::BossBullet>& bullet : bullets_) {
			bullet->Draw(viewProjection_);
		}
	}
}

void MyEngine::Boss::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class MyEngine::PlayerBullet";

	//相手がplayerの弾
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isHit == false && isInvisible == false) {
			isHit = true;
			hitTimer = HIT_TIME_MAX;
			hp-= DAMAGE_NUM;
			for (int i = 0; i < PARTS_NUM; i++) {
				if (parts[i]->GetIsLocked() == true) {
					parts[i]->SetIsLocked(false);
					hp -= DAMAGE_NUM;
				}
			}
		}
	}
}

void MyEngine::Boss::SkipMovie()
{
	appearTimer = 0;
	SetPosition(bossSkipPos);
	bossAlpha = MAX_ALPHA;
}

void MyEngine::Boss::SlainUpdate()
{
	//乱数生成装置
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(-5.0f, 5.0f);
	Vector3 randomNum(dist(engine), dist(engine), dist(engine));

	if (slainTimer < SLAIN_TIME) {
		SetRotation(randomNum);		
	}
	else{
		isSlained = true;
	}

	GetWorldTransform().UpdateMatrix();
	slainTimer++;
}
