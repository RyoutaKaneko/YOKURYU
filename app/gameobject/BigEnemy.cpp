/**
 * @file BigEnemy.h
 * @brief でか敵クラス
 * @author カネコ_リョウタ
 */

#include "BigEnemy.h"

MyEngine::BigEnemy::~BigEnemy()
{
}

void MyEngine::BigEnemy::BigInitialize()
{
	Initialize();
	shadow = new Object3d;
	shadow->Initialize();
	// OBJからモデルデータを読み込む
	enemyModel = Model::LoadFromOBJ("enemy");
	enemyModel->LoadTexture("Resources/enemy/genemy.png");
	shadowModel = Model::LoadFromOBJ("panel");
	shadowModel->LoadTexture("Resources/shadow.png");
	shadow = Object3d::Create();
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(enemyModel);
	SetRotation({ 0,290,0 });
	SetScale({ 2,2,2 });
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
	popReq = false;
}

void MyEngine::BigEnemy::BigUpdate(const Vector3& pPos, MyEngine::RailCamera* rail)
{
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
		//とりあえず回してみる
		SetRotation(GetRotation() + rotePower);

		//ふわふわ浮く
		if (timer < MOVE_TIME_ONE) {
			SetPosition(GetPosition() + Vector3(0, UPDOWN_POWER, 0));
		}
		else if (timer < MOVE_TIME_TWO) {
			SetPosition(GetPosition() + Vector3(0, -UPDOWN_POWER, 0));
		}
		else {
			timer = 0;
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
			Vector3 playerVec = pPos - GetPosition();
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
				if (isParticle == false) {
					isParticle = true;
					popReq = true;
				}
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
			bullet->Update(pPos, isParticle);
		}
		//デスフラグの立った弾を削除
		bullets_.remove_if([](std::unique_ptr <MyEngine::EnemyBullet>& bullets) {
			return bullets->IsDead();
			});

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

void MyEngine::BigEnemy::BigDraw(ViewProjection* viewProjection_)
{
	if (isParticle == false) {
		Draw(viewProjection_, alpha);
		shadow->Draw(viewProjection_, alpha);
	}
	for (std::unique_ptr<MyEngine::Energy>& particle : deadParticles) {
		particle->Draw(viewProjection_, 0.8f);
	}
}

void MyEngine::BigEnemy::OnCollision([[maybe_unused]] const CollisionInfo& info)
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
