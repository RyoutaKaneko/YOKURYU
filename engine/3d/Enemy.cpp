#include "Enemy.h"
#include "string.h"

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
	timer = 0;
}

void Enemy::Update() {
	if (timer < 75) {
		SetPosition(GetPosition() + Vector3( 0, 0.005f, 0 ));
	}
	else if (timer < 150) {
		SetPosition(GetPosition() + Vector3(0, -0.005f, 0));
	}
	else {
		timer = 0;
	}

	worldTransform_.UpdateMatrix();
	timer++;
}

//void Enemy::OnCollision(const CollisionInfo& info)
//{
//	const char* str1 = "class Player";
//
//	//���肪player
//	if (strcmp(toCollisionName, str1) == 0) {
//		isDead_ = true;
//	}
//}
//
//void Enemy::OffCollision(const CollisionInfo& info)
//{
//
//}