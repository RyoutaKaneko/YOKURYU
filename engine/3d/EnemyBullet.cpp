#include "EnemyBullet.h"
#include "BaseCollider.h"

void EnemyBullet::BulletInitialize(const Vector3& position) {

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
	if (bulletTime < 20) {
		velocity = (playerPos_ - GetPosition()) * 0.02f;
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

void EnemyBullet::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Player";

	//���肪enemy
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}
