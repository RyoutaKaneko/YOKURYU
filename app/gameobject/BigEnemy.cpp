/**
 * @file BigEnemy.h
 * @brief �ł��G�N���X
 * @author �J�l�R_�����E�^
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
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("enemy");
	enemyModel->LoadTexture("Resources/enemy/genemy.png");
	shadowModel = Model::LoadFromOBJ("panel");
	shadowModel->LoadTexture("Resources/shadow.png");
	shadow = Object3d::Create();
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
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
	//player��ʂ�z�����������
	if (stagePoint < rail->GetPasPoint() + 0.8f) {
		isDead_ = true;
	}
	//������ԂȂ�
	if (isInvisible == true) {
		//�߂Â����Ƃ��ɏo��
		float len = stagePoint - rail->GetPasPoint() + 1.0f;
		if (len < POP_RANGE) {
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

		//�ӂ�ӂ핂��
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
		//player���G��ǂ��z������U�����Ȃ�
		if (stagePoint < rail->GetPasPoint() + 1.0f) {
			if (isAttack == true) {
				isAttack = false;
			}
		}
		//�U��
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
		//���S�����o
		if (isHit == true) {
			//�j�􂳂���
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
		//�e�̍X�V
		for (std::unique_ptr<MyEngine::EnemyBullet>& bullet : bullets_) {
			bullet->Update(pPos, isParticle);
		}
		//�f�X�t���O�̗������e���폜
		bullets_.remove_if([](std::unique_ptr <MyEngine::EnemyBullet>& bullets) {
			return bullets->IsDead();
			});

		//�e
		Vector3 spos = GetPosition();
		shadow->SetPosition({ spos.x,-5,spos.z });
		shadow->Update();

		//�����蔻��X�V
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
	//�Փˑ���̖��O
	const char* str1 = "class MyEngine::PlayerBullet";

	//���肪player�̒e
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isInvisible == false) {
			if (isHit == false) {
				isHit = true;
			}
		}
	}
}
