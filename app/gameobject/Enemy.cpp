/**
 * @file Enemy.h
 * @brief enemyの全般(ステータス、行動、描画)をまとめたクラス
 * @author カネコ_リョウタ
 */

#include "Enemy.h"
#include "string.h"
#include "BaseCollider.h"
#include "SphereCollider.h"
#include "GameScene.h"

const float MyEngine::Enemy::MOVE_POWER = 0.05f;
const float MyEngine::Enemy::UPDOWN_POWER = 0.005f;
const float MyEngine::Enemy::MAX_ALPHA = 1.0f;
const float MyEngine::Enemy::ATTACK_RANGE = 70.0f;
const Vector3 MyEngine::Enemy::ADDSCALE = { 0.5f,0.5f,0.5f };
const float MyEngine::Enemy::POP_RANGE = 3.0f;
const float MyEngine::Enemy::SHADOW_Y = -4.92f;

//デストラクタ
MyEngine::Enemy::~Enemy() {
	delete shadow;
	delete shadowModel;
}

//初期化
void MyEngine::Enemy::EnemyInitialize()
{
	Initialize();
	shadow = new Object3d;
	shadow->Initialize();
	// OBJからモデルデータを読み込む
	enemyModel = Model::LoadFromOBJ("enemy");
	shadowModel = Model::LoadFromOBJ("panel");
	shadowModel->LoadTexture("Resources/shadow.png");
	shadow = Object3d::Create();
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(enemyModel);
	SetRotation({ 0,290,0 });
	shadow->SetModel(shadowModel);
	shadow->SetRotation({ 0,0,90 });
	isDead_ = false;
	isInvisible = true;
	isLocked = false;
	timer = 0;
	isAttack = false;
	timeCount = 0;
	alpha = 0;
	deathTimer = DEATH_TIMER;
	isHit = false;
	rotePower = { 0,2,0 };
	movePower = 0.0f;
}

void MyEngine::Enemy::Update(const Vector3& velo, MyEngine::RailCamera* rail) {
	//playerを通り越したら消える
	if (stagePoint < rail->GetPasPoint() + 0.8f) {
		isDead_ = true;
	}
	//透明状態なら
	if (isInvisible == true) {
		//近づいたときに出現
		float len = stagePoint - rail->GetPasPoint() + 1.0f;
		if (len < POP_RANGE) {
			isInvisible = false;
		}
	}
	//出現
	else {
		//透過状態を解除
		if (alpha < MAX_ALPHA) {
			alpha += MOVE_POWER;
		}
		//左右に動く
		float moveX;
		if (timeCount == 0) {
			moveX = -MOVE_POWER;
		}
		else if (timeCount == 1) {
			moveX = MOVE_POWER;
		}
		else if (timeCount == 2) {
			moveX = MOVE_POWER;
		}
		else {
			moveX = -MOVE_POWER;
		}
		//とりあえず回してみる
		SetRotation(GetRotation() + rotePower);

		//ふわふわ浮く
		if (timer < MOVE_TIME_ONE) {
			if (movePower != 0) {
				SetPosition(GetPosition() + Vector3(movePower + movePower, UPDOWN_POWER, 0));
			}
			else {
				SetPosition(GetPosition() + Vector3(moveX + movePower, UPDOWN_POWER, 0));
			}
		}
		else if (timer < MOVE_TIME_TWO) {
			if (movePower != 0) {
				SetPosition(GetPosition() + Vector3(movePower + movePower, UPDOWN_POWER, 0));
			}
			else {
				SetPosition(GetPosition() + Vector3(moveX + movePower, -UPDOWN_POWER, 0));
			}
		}
		else {
			timer = 0;
			movePower = 0.0f;
			if (timeCount == TIMECOUNT_MAX) {
				timeCount = 0;
			}
			else {
				timeCount++;
			}
		}
		//playerが敵を追い越したら攻撃しない
		if (stagePoint < rail->GetPasPoint() + 1.0f) {
			if (isAttack == true) {
				isAttack = false;
			}
		}
		//攻撃
		if (isAttack == false && isParticle == false) {
			Vector3 playerVec = velo - GetPosition();
			float len = playerVec.length();
			if (len < ATTACK_RANGE) {
				isAttack = true;
			}
		}
		else {
			Attack();
		}
		//死亡時演出
		if (isHit == true) {
			//破裂させる
			if (GetScale().x < SCALE_MAX) {
				SetScale(GetScale() + ADDSCALE);
				alpha -= subAlpha;
			}
			else {
				isParticle = true;
			}
		}
		if (isParticle == true) {
			//死亡時パーティクル
			if (deathTimer > DEAD_PARTICLE) {
				PopParticle();
			}
			else if (deathTimer == 0) {
				isDead_ = true;
			}
			deathTimer--;
		}
		//更新
		for (std::unique_ptr<MyEngine::Energy>& particle : deadParticles) {
			particle->Update(rail->GetCamera()->GetRotation());
		}
		//パーティクルを削除
		deadParticles.remove_if([](std::unique_ptr <MyEngine::Energy>& particle) {
			return particle->GetIsDead();
			});
		//弾の更新
		for (std::unique_ptr<MyEngine::EnemyBullet>& bullet : bullets_) {
			bullet->Update(velo, isParticle);
		}
		//デスフラグの立った弾を削除
		bullets_.remove_if([](std::unique_ptr <MyEngine::EnemyBullet>& bullets_) {
			return bullets_->IsDead();
			});

		if (movePower > 0) {
			movePower -= 0.1f;
		}
		else if (movePower < 0) {
			movePower += 0.1f;
		}
		else {};

		//影
		Vector3 spos = GetPosition();
		shadow->SetPosition({ spos.x,-5,spos.z });
		shadow->Update();

		//当たり判定更新
		if (collider)
		{
			if (isParticle == false) {
				collider->Update();
			}
		}
		GetWorldTransform().UpdateMatrix();
		timer++;
	}
}

void MyEngine::Enemy::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class MyEngine::PlayerBullet";

	//相手がplayerの弾
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isInvisible == false) {
			if (isHit == false) {
				isHit = true;
			}
		}
	}
}

void MyEngine::Enemy::PopParticle()
{
	//弾を生成し初期化
	std::unique_ptr<MyEngine::Energy> particle = std::make_unique<MyEngine::Energy>();
	particle->EnergyInitialize("dp");
	particle->SetPosition(GetPosition());
	deadParticles.push_back(std::move(particle));

}

void MyEngine::Enemy::Attack() {

	if (coolTime == 0) {
		//弾を生成し初期化
	//複数
		std::unique_ptr<MyEngine::EnemyBullet> newBullet = std::make_unique<MyEngine::EnemyBullet>();

		//単発													   
		newBullet->BulletInitialize();
		newBullet->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.5f));

		//弾の登録										 
	   //複数
		newBullet->SetPosition(GetPosition());
		newBullet->SetScale({ 0.3f,0.3f,0.3f });
		bullets_.push_back(std::move(newBullet));


		//クールタイムを設定
		coolTime = COOLTIME_MAX;
	}
	else if (coolTime > 0) {
		coolTime--;
	}

}

void MyEngine::Enemy::EnemyDraw(ViewProjection* viewProjection_) {
	if (isParticle == false) {
		Draw(viewProjection_, alpha);
		shadow->Draw(viewProjection_, alpha);
	}
	//弾描画
	for (std::unique_ptr<MyEngine::EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
	for (std::unique_ptr<MyEngine::Energy>& particle : deadParticles) {
		particle->Draw(viewProjection_, 0.8f);
	}
}