#include "BossBullet.h"
#include "BaseCollider.h"

void BossBullet::BulletInitialize(const Vector3& position)
{
	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	bulletModel = Model::LoadFromOBJ("triangle_mat");
	bulletModel->LoadTexture("Resources/blue.png");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bulletModel);

	//�̗͎w��
	hp = 2;
	hitTime = 0;
	isHit = false;
}

void BossBullet::Update(const Vector3& playerPos_)
{
	//�ړ��x�N�g�����v�Z
	velocity = playerPos_ - GetPosition();
	velocity.normalize();
	//���W�����Z
	SetPosition(GetPosition() + velocity);
	//�X�V
	worldTransform_.UpdateMatrix();

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
			bulletModel->LoadTexture("Resources/red.png");
		}
	}
	else {
		if (isHit == true) {
			isHit = false;
			bulletModel->LoadTexture("Resources/blue.png");
		}
	}
	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void BossBullet::OnCollision(const CollisionInfo& info)
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
		if (hitTime == 0) {
			if (hp == 2) {
				hp--;
			}
			else {
				isDead_ = true;
				hitTime = 10;
			}
		}
	}
}
