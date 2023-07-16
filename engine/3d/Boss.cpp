#include "Boss.h"
#include "SphereCollider.h"

Boss::~Boss()
{
	delete bossModel;
}

void Boss::BossInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	bossModel = Model::LoadFromOBJ("triangle_mat");
	bossModel->LoadTexture("Resources/red.png");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bossModel);
	SetPosition({ 0,15,-200 });
	SetScale({ 10,10,10 });
	isDead_ = false;
	isInvisible = true;
	//�^�C�}�[
	bossTimer = 0;
	bossAlpha = 0.0f;
}

void Boss::Update()
{
	if (bossTimer > 0) {
		SetPosition(GetPosition() + Vector3(0, -0.1f, 0));
		if (bossTimer > 100) {
			bossAlpha += 0.02f;
		}
		bossTimer--;
	}
	else {
		int a = 0;
	}
	worldTransform_.UpdateMatrix();
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}

void Boss::Pop()
{
	if (isInvisible == true) {
		isInvisible = false;
	}
	bossTimer = 150;

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
