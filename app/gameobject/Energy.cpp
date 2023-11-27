/**
 * @file Energy.h
 * @brief �K�E�Z�ɕK�v�ȃG�l���M�[�p�N���X
 * @author �J�l�R_�����E�^
 */

#include "Energy.h"
#include "string.h"
#include "BaseCollider.h"
#include "SphereCollider.h"

void Energy::EnergyInitialize(const std::string &model_)
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	energyModel = Model::LoadFromOBJ(model_);
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(energyModel);
	SetScale(Vector3(0.5f, 0.5f, 0.5f));
	isDead = false;				

	std::mt19937_64 engine(seed_gen());
	std::uniform_real_distribution<float>dist(-0.1f, 0.1f);
	std::uniform_real_distribution<float>dist2(-0.1f, 0.1f);
	randomNum = { dist(engine), dist2(engine), dist2(engine) };
}

void Energy::Update(Vector3 pos,Vector3 rot)
{
	//player�̂��Ƃ�
	Vector3 velo = pos - GetPosition();
	velo = velo.normalize();
	SetPosition(GetPosition() + velo);
	SetRotation(rot + Vector3(0,90,0));

	GetWorldTransform().UpdateMatrix();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}

void Energy::DeadEffect()
{
	//�����������u


	SetPosition(GetPosition() + randomNum);
	Vector3 minScale(0.01f, 0.01f, 0.01f);
	SetScale(GetScale() - minScale);

	GetWorldTransform().UpdateMatrix();
}

void Energy::OnCollision([[maybe_unused]] const CollisionInfo& info)
{
	//�Փˑ���̖��O
	const char* str1 = "class Player";

	//���肪player�̒e
	if (strcmp(GetToCollName(), str1) == 0) {
		if (isDead == false) {
			isDead = true;
		}
	}
}
