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
	bossModel = Model::LoadFromOBJ("fighter");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(bossModel);
	SetPosition({ -15,15,-200 });
	SetScale({ 10,10,10 });
	isDead_ = false;
	isInvisible = true;
	//�^�C�}�[
	appearTimer = 0;
	bossAlpha = 0.0f;
	hp = 30;
	isHit = false;
	hitTimer = 0;
	timer = 0;
	timeCount = 0;
}

void Boss::Update()
{
	if (appearTimer > 0) {
		if (appearTimer > 150) {
			SetPosition(GetPosition() + Vector3(0.5f, -0.1f, 0));
		}
		if (appearTimer > 100) {
			bossAlpha += 0.02f;
		}
		appearTimer--;
	}
	//�{�X�o���
	else {
		
	}
	if (hitTimer > 0) {
		hitTimer--;
		if (hitTimer == 0) {
			isHit = false;
		}
	}
	if (hp == 0) {
		isDead_ = true;
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
	appearTimer = 300;

}

void Boss::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class PlayerBullet";

	//���肪player�̒e
	if (strcmp(toCollisionName, str1) == 0) {
		if (isHit == false && isInvisible == false) {
			isHit = true;
			hitTimer = 30;
			hp--;
		}
	}
}
