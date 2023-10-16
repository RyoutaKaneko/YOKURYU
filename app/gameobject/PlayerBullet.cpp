/**
 * @file PlayerBullet.h
 * @brief �v���C���[�̍U���Ɏg���e���X�g�p�N���X
 * @author �J�l�R_�����E�^
 */

#include "PlayerBullet.h"
#include "BaseCollider.h"

void PlayerBullet::BulletInitialize(const Vector3& velocity) {

	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	bulletModel = Model::LoadFromOBJ("triangle_mat");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bulletModel);

	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void PlayerBullet::Update() {

	SetPosition(GetPosition() + velocity_);

	worldTransform_.UpdateMatrix();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void PlayerBullet::HomingVec()
{
	if (isHoming == true) {
		velocity_ = lockObj->GetWorldPos() - GetPosition();
		velocity_ = velocity_ * 0.25f;
	}
}

void PlayerBullet::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Enemy";
	const char* str2 = "class EnemyBullet";
	const char* str3 = "class Boss";
	const char* str4 = "class BossBullet";

	//���肪enemy
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}

	//���肪enemy�̒e
	if (strcmp(toCollisionName, str2) == 0) {
		if (isDead_ == false && isHoming == false) {
			isDead_ = true;
		}
	}
	//���肪�{�X
	if (strcmp(toCollisionName, str3) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}

	//���肪�{�X�̒e
	if (strcmp(toCollisionName, str4) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}

}