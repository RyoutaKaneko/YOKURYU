#include "Enemy.h"
#include "string.h"
#include "BaseCollider.h"

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
	/*SetCollider(new SphereCollider);*/
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
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
	worldTransform_.UpdateMatrix();
	timer++;
}

void Enemy::OnCollision(const CollisionInfo& info)
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