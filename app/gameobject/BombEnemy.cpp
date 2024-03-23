/**
 * @file BombEnemy.h
 * @brief �˂�����ł��Ĕ�������G�N���X
 * @author �J�l�R_�����E�^
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
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("enemy");
	enemyModel->LoadTexture("Resources/benemy.png");
	shadowModel = Model::LoadFromOBJ("panel");
	shadowModel->LoadTexture("Resources/shadow.png");
	shadow = Object3d::Create();
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
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
	//player��ʂ�z�����������
	if (stagePoint < rail->GetPasPoint() + 1.1f) {
		isDead_ = true;
	}
	//������ԂȂ�
	if (isInvisible == true) {
		//�߂Â����Ƃ��ɏo��
		float len = stagePoint - rail->GetPasPoint() + 1.0f;
		if (len < 2.5f) {
			isInvisible = false;
		}
	}
	//�o��
	else {
		//���ߏ�Ԃ�����
		if (alpha < MAX_ALPHA) {
			alpha += MOVE_POWER;
		}
		//�Ƃ肠�����񂵂Ă݂�
		SetRotation(GetRotation() + rotePower);

		//�o����
		if (popTime < 40) {
			SetPosition(GetPosition() + Vector3(0, 0.2f, 0));
			popTime++;
		}
		else {
			BombAttack(pPos);
		}

		//���S�����o
		if (isHit == true) {
			//�j�􂳂���
			if (GetScale().x < SCALE_MAX) {
				SetScale(GetScale() + ADDSCALE);
				alpha -= subAlpha;
			}
			else {
				isParticle = true;
			}
		}
		if (isParticle == true) {
			//���S���p�[�e�B�N��
			if (deathTimer > DEAD_PARTICLE) {
				PopParticle();
			}
			else if (deathTimer == 0) {
				isDead_ = true;
			}
			deathTimer--;
		}
		//�X�V
		for (std::unique_ptr<MyEngine::Energy>& particle : deadParticles) {
			particle->Update(rail->GetCamera()->GetRotation());
		}
		//�p�[�e�B�N�����폜
		deadParticles.remove_if([](std::unique_ptr <MyEngine::Energy>& particle) {
			return particle->GetIsDead();
			});

		//�e
		Vector3 spos = GetPosition();
		shadow->SetPosition({ spos.x,-5,spos.z });
		shadow->Update();

		//�����蔻��X�V
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
	//�Փˑ���̖��O
	const char* str1 = "class MyEngine::PlayerBullet";
	const char* str2 = "class MyEngine::Player";

	//���肪player�̒e
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isInvisible == false) {
			if (isHit == false) {
				isHit = true;
			}
		}
	}

	//���肪player
	if (strcmp(GetToCollName(), str2) == 0) {
		if (isInvisible == false) {
			if (isDead_ == false) {
				isDead_ = true;
			}
		}
	}
}