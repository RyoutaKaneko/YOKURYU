#include "Boss.h"

Boss::~Boss()
{
	delete bossModel;
}

void Boss::BossInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	bossModel = Model::LoadFromOBJ("triangle_mat");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bossModel);
	isDead_ = false;
}

void Boss::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class PlayerBullet";

	//���肪player�̒e
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead_ == false) {
			isDead_ = true;
		}
	}
}
