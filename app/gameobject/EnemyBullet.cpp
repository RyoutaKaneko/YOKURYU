/**
 * @file EnemyBullet.h
 * @brief �ʏ�G�U���Ɏg���e���X�g�p�N���X
 * @author �J�l�R_�����E�^
 */

#include "EnemyBullet.h"
#include "BaseCollider.h"

void EnemyBullet::BulletInitialize() {

	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	bulletModel = Model::LoadFromOBJ("triangle_mat");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bulletModel);

	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	bulletTime = 0;
}

void EnemyBullet::Update(const Vector3& playerPos_) {

	if (bulletTime < 40) {
		velocity = (playerPos_ - GetPosition()) * 0.05f;
		bulletTime++;
	}

	SetPosition(GetPosition() + velocity);

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

void EnemyBullet::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Player";
	const char* str2 = "class PlayerBullet";

	//���肪player
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
	//���肪player�̒e
	if (strcmp(toCollisionName, str2) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}
