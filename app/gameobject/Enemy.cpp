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

//�f�X�g���N�^
Enemy::~Enemy() {
	delete enemyModel;
}

//������
void Enemy::EnemyInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("triangle_mat");
	enemyModel->LoadTexture("Resources/red.png");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(enemyModel);
	isDead_ = false;
	isInvisible = true;
	timer = 0;
	isAttack = false;
	timeCount = 0;
	alpha = 0;
	deathTimer = DEATH_TIMER;
}

void Enemy::Update(Vector3 velo, RailCamera* rail) {
	//������ԂȂ�
	if (isInvisible == true) {
		float len = stagePoint - rail->GetPasPoint() + 1.0f;
 		if (len < 4.0f) {
			isInvisible = false;
		}
	}
	else {
		if (alpha < 1) {
			alpha += 0.05f;
		}
		float moveX;
		if (timeCount == 0) {
			moveX = -0.05f;
		}
		else if (timeCount == 1) {
			moveX = 0.05f;
		}
		else if (timeCount == 2) {
			moveX = 0.05f;
		}
		else {
			moveX = -0.05f;
		}

		if (timer < 75) {
			SetPosition(GetPosition() + Vector3(moveX, 0.005f, 0));
		}
		else if (timer < 150) {
			SetPosition(GetPosition() + Vector3(moveX, -0.005f, 0));
		}
		else {
			timer = 0;
			if (timeCount == 4) {
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
		if (isAttack == false) {
			Vector3 playerVec = velo - GetPosition();
			float len = playerVec.length();
			if (len < 70.0f) {
				isAttack = true;
			}
		}
		else {
			Attack();
		}
		//���S�����o
		if (isParticle == true) {
			if (deathTimer > 45) {
				PopParticle();
			}
			else if (deathTimer == 0) {
				isDead_ = true;
			}
			//�X�V
			for (std::unique_ptr<Energy>& particle : deadParticles) {
				particle->DeadEffect(rail->GetCamera()->GetRotation());
			}

			deadParticles.remove_if([](std::unique_ptr <Energy>& particle) {
				return particle->GetIsDead();
				});

			deathTimer--;
		}

		for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
			bullet->Update(velo);
		}
		//�f�X�t���O�̗������e���폜
		bullets_.remove_if([](std::unique_ptr <EnemyBullet>& bullets_) {
			return bullets_->IsDead();
			});
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

void Enemy::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class PlayerBullet";

	//���肪player�̒e
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isInvisible == false) {
			if (isParticle == false) {
				isParticle = true;
			}
		}
	}
}

void Enemy::PopParticle()
{
	//�e�𐶐���������
													   
	for (int i = 0; i < 1; i++) {
		std::unique_ptr<Energy> particle = std::make_unique<Energy>();
		particle->EnergyInitialize("dp");
		particle->SetPosition(GetPosition());
		deadParticles.push_back(std::move(particle));
	}
}

void Enemy::Attack() {

		if (coolTime == 0) {
			//�e�𐶐���������
		//����
			std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();

			//�P��													   
			newBullet->BulletInitialize();
			newBullet->SetCollider(new SphereCollider(Vector3{0,0,0},0.5f));

			//�e�̓o�^										 
		   //����
			newBullet->SetPosition(GetPosition());
			newBullet->SetScale({ 0.3f,0.3f,0.3f });
			bullets_.push_back(std::move(newBullet));


			//�N�[���^�C����ݒ�
			coolTime = 200;
		}
		else if (coolTime > 0) {
			coolTime--;
		}

}

void Enemy::EnemyDraw(ViewProjection* viewProjection_) {
	if (isParticle == false) {
		Draw(viewProjection_, alpha);
	}
	//�e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
	for (std::unique_ptr<Energy>& particle : deadParticles) {
		particle->Draw(viewProjection_,0.8f);
	}
}