/**
 * @file BombEnemy.h
 * @brief 突っ込んできて爆発する敵クラス
 * @author カネコ_リョウタ
 */

#include "BombEnemy.h"

MyEngine::BombEnemy::~BombEnemy()
{

}

void MyEngine::BombEnemy::BombInitialize()
{
	Initialize();
	shadow = new Object3d;
	shadow->Initialize();
	// OBJからモデルデータを読み込む
	enemyModel = Model::LoadFromOBJ("enemy");
	enemyModel->LoadTexture("Resources/benemy.png");
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
}

void MyEngine::BombEnemy::BombUpdate(const Vector3& pPos, MyEngine::RailCamera* rail)
{
	//playerを通り越したら消える
	if (stagePoint < rail->GetPasPoint() + 1.1f) {
		isDead_ = true;
	}
	//透明状態なら
	if (isInvisible == true) {
		//近づいたときに出現
		float len = stagePoint - rail->GetPasPoint() + 1.0f;
		if (len < 2.5f) {
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

		//出現後
		if (popTime < 40) {
			SetPosition(GetPosition() + Vector3(0, 0.2f, 0));
			popTime++;
		}
		else {
			BombAttack(pPos);
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

		//影
		Vector3 spos = GetPosition();
		shadow->SetPosition({ spos.x,-5,spos.z });
		shadow->Update();

		//当たり判定更新
		if (collider)
		{
			if (isInvisible == false && isParticle == false) {
				collider->Update();
			}
		}
		GetWorldTransform().UpdateMatrix();
		timer++;
	}
}

void MyEngine::BombEnemy::BombDraw(ViewProjection* viewProjection_)
{
	if (isParticle == false) {
		Draw(viewProjection_, alpha);
		shadow->Draw(viewProjection_, alpha);
	}
	for (std::unique_ptr<MyEngine::Energy>& particle : deadParticles) {
		particle->Draw(viewProjection_, 0.8f);
	}
}

void MyEngine::BombEnemy::BombAttack(const Vector3& pPos)
{
	Vector3 attackVelo = pPos - GetPosition();
	attackVelo = attackVelo.normalize();
	attackVelo *= 0.5f;
	SetPosition(GetPosition() + attackVelo);
}

void MyEngine::BombEnemy::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//衝突相手の名前
	const char* str1 = "class MyEngine::PlayerBullet";
	const char* str2 = "class MyEngine::Player";

	//相手がplayerの弾
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isInvisible == false) {
			if (isHit == false) {
				isHit = true;
			}
		}
	}

	//相手がplayer
	if (strcmp(GetToCollName(), str2) == 0) {
		if (isInvisible == false) {
			if (isDead_ == false) {
				isDead_ = true;
			}
		}
	}
}