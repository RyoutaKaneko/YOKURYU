/**
 * @file PlayerBullet.h
 * @brief �v���C���[�̍U���Ɏg���e���X�g�p�N���X
 * @author �J�l�R_�����E�^
 */

#include "PlayerBullet.h"
#include "BaseCollider.h"

const float MyEngine::PlayerBullet::correction = 0.25f;

void MyEngine::PlayerBullet::BulletInitialize(const Vector3& velocity) {

	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	bulletModel = Model::LoadFromOBJ("bullet");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bulletModel);
	SetScale({ 3.0,3.0,3.0 });

	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
}

void MyEngine::PlayerBullet::Update() {

	SetPosition(GetPosition() + velocity_);

	GetWorldTransform().UpdateMatrix();

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

void MyEngine::PlayerBullet::HomingVec()
{
	//���b�N�I����ɔ��ł���
	if (isHoming == true) {
		velocity_ = lockObj->GetWorldPos() - GetPosition();
		velocity_ = velocity_ * correction;
	}
}

void MyEngine::PlayerBullet::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class MyEngine::Enemy";
	const char* str2 = "class MyEngine::Boss";
	const char* str3 = "class MyEngine::BossBullet";

	//���肪enemy
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}

	//���肪�{�X
	if (strcmp(GetToCollName(), str2) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
	//���肪�{�X�̒e
	if (strcmp(GetToCollName(), str3) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}

}