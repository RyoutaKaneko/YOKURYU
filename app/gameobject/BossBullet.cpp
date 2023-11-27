/**
 * @file BossBullet.h
 * @brief �{�X�U���Ɏg���e���X�g�p�N���X
 * @author �J�l�R_�����E�^
 */

#include "BossBullet.h"
#include "BaseCollider.h"

void BossBullet::BulletInitialize()
{
	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	bulletModel = Model::LoadFromOBJ("bossBullet");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bulletModel);

	//�̗͎w��
	hp = 3;
	hitTime = 0;
	isHit = false;
}

void BossBullet::Update(const Vector3& playerPos_)
{
	//�ړ��x�N�g�����v�Z
	velocity = playerPos_ - GetPosition();
	velocity.normalize();
	//���W�����Z
	SetPosition(GetPosition() + (velocity * 0.5f));
	//�X�V
	GetWorldTransform().UpdateMatrix();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	//�q�b�g���N�[���^�C��
	if (hitTime > 0) {
		hitTime--;
		if (isHit == false) {
			isHit = true;
			bulletModel->LoadTexture("Resources/bossBullet/stonedmg.png");
		}
	}
	else {
		if (isHit == true) {
			isHit = false;
			if (hp == 2) {
				bulletModel->LoadTexture("Resources/bossBullet/stone3.png");
			}
			else if (hp == 1) {
				bulletModel->LoadTexture("Resources/bossBullet/stone3.png");
			}
		}
	}
	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void BossBullet::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Player";
	const char* str2 = "class PlayerBullet";

	//���肪player
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
	//���肪player�̒e
	if (strcmp(GetToCollName(), str2) == 0) {
		if (hitTime == 0) {
			if (hp <= 0) {
				isDead_ = true;
			}
			else {
				hp--;
				hitTime = 10;
			}
		}
	}
}
