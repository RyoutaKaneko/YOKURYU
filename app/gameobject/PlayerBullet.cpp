/**
 * @file PlayerBullet.h
 * @brief �v���C���[�̍U���Ɏg���e���X�g�p�N���X
 * @author �J�l�R_�����E�^
 */

#include "PlayerBullet.h"
#include "BaseCollider.h"

const float MyEngine::PlayerBullet::correction = 0.0001f;
const float MyEngine::PlayerBullet::ADD_ACCEL = 0.2f;
const int MyEngine::PlayerBullet::HOMING_TIME = 5;

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
	homingTime = 0;
	accel = 1.4f;
}

void MyEngine::PlayerBullet::Update() {

	//�X�V
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
		if (homingTime < HOMING_TIME) {
			homingTime++;
			if (homingTime == HOMING_TIME) {
				lockPos = GetWorldPos();
			}
		}
		else if(homingTime >= HOMING_TIME) {
			//v1,v2�����߂�
			Vector3 toPlayer = lockObj->GetWorldPos() - GetPosition();
			toPlayer = toPlayer.normalize();
			velocity_ = velocity_.normalize();
			float t = 0.5f;
			//���ʐ��`�⊮����
			velocity_ = Vector3::Slerp(velocity_, toPlayer, t) * accel;
		}
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
		if (isHoming == false) {
			if (isDead_ == false) {
				isDead_ = true;
			}
		}
		else {
			if (info.object == lockObj) {
				if (isDead_ == false) {
					isDead_ = true;
				}
			}
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
		if (isHoming == false) {
			if (isDead_ == false) {
				isDead_ = true;
			}
		}
	}
}