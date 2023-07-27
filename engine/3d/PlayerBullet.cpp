#include "PlayerBullet.h"
#include "BaseCollider.h"

void PlayerBullet::BulletInitialize(const Vector3& velocity) {

	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	bulletModel = Model::LoadFromOBJ("ironSphere");
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

void PlayerBullet::HomingVec(Vector3 pos)
{
	if (isHoming == true) {
		velocity_ = lockObj->GetWorldPos() - GetPosition();
		velocity_ = velocity_ * 0.25f;
	}
}

void PlayerBullet::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Enemy";
	const char* str2 = "class EnemyBullet";

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
}
