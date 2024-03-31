/**
 * @file Enemy.h
 * @brief enemy�̑S��(�X�e�[�^�X�A�s���A�`��)���܂Ƃ߂��N���X
 * @author �J�l�R_�����E�^
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

//�f�X�g���N�^
MyEngine::Enemy::~Enemy() {
	delete shadow;
	delete shadowModel;
}

//������
void MyEngine::Enemy::EnemyInitialize()
{
	Initialize();
	shadow = new Object3d;
	shadow->Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("enemy");
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
	movePower = 0.0f;
}

void MyEngine::Enemy::Update(const Vector3& velo, MyEngine::RailCamera* rail) {
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
		//���E�ɓ���
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
		//�Ƃ肠�����񂵂Ă݂�
		SetRotation(GetRotation() + rotePower);

		//�ӂ�ӂ핂��
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
		//player���G��ǂ��z������U�����Ȃ�
		if (stagePoint < rail->GetPasPoint() + 1.0f) {
			if (isAttack == true) {
				isAttack = false;
			}
		}
		//�U��
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
		//�e�̍X�V
		for (std::unique_ptr<MyEngine::EnemyBullet>& bullet : bullets_) {
			bullet->Update(velo, isParticle);
		}
		//�f�X�t���O�̗������e���폜
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

void MyEngine::Enemy::OnCollision([[maybe_unused]] const CollisionInfo& info)
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

void MyEngine::Enemy::PopParticle()
{
	//�e�𐶐���������
	std::unique_ptr<MyEngine::Energy> particle = std::make_unique<MyEngine::Energy>();
	particle->EnergyInitialize("dp");
	particle->SetPosition(GetPosition());
	deadParticles.push_back(std::move(particle));

}

void MyEngine::Enemy::Attack() {

	if (coolTime == 0) {
		//�e�𐶐���������
	//����
		std::unique_ptr<MyEngine::EnemyBullet> newBullet = std::make_unique<MyEngine::EnemyBullet>();

		//�P��													   
		newBullet->BulletInitialize();
		newBullet->SetCollider(new SphereCollider(Vector3{ 0,0,0 }, 0.5f));

		//�e�̓o�^										 
	   //����
		newBullet->SetPosition(GetPosition());
		newBullet->SetScale({ 0.3f,0.3f,0.3f });
		bullets_.push_back(std::move(newBullet));


		//�N�[���^�C����ݒ�
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
	//�e�`��
	for (std::unique_ptr<MyEngine::EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
	for (std::unique_ptr<MyEngine::Energy>& particle : deadParticles) {
		particle->Draw(viewProjection_, 0.8f);
	}
}