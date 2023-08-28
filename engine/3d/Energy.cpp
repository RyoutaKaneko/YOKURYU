#include "Energy.h"
#include "string.h"
#include "BaseCollider.h"
#include "SphereCollider.h"

void Energy::EnergyInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	energyModel = Model::LoadFromOBJ("panel");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(energyModel);
	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isDead = false;
}

void Energy::Update(Vector3 pos,Vector3 rot)
{
	//player�̂��Ƃ�
	Vector3 velo = pos - GetPosition();
	velo = velo.normalize();
	SetPosition(GetPosition() + velo);
	SetRotation(rot + Vector3(0,90,0));

	worldTransform_.UpdateMatrix();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}

void Energy::OnCollision(const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Player";

	//���肪player�̒e
	if (strcmp(toCollisionName, str1) == 0) {
		if (isDead == false) {
			isDead = true;
		}
	}
}
