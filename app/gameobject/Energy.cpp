/**
 * @file Energy.h
 * @brief �K�E�Z�ɕK�v�ȃG�l���M�[�p�N���X
 * @author �J�l�R_�����E�^
 */

#include "Energy.h"
#include "string.h"
#include "BaseCollider.h"
#include "SphereCollider.h"

const Vector3 Energy::ROTATE = { 0,90,0 };
const Vector3 Energy::SUB_SCALE = { 0.01f, 0.01f, 0.01f };
const float Energy::MIN_SCALE = 0.01f;

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

void Energy::Update(Vector3 rot)
{
	//�����������u


	SetPosition(GetPosition() + randomNum);
	SetScale(GetScale() - SUB_SCALE);
	SetRotation(rot + ROTATE);

	if (GetScale().x < MIN_SCALE) {
		isDead = true;
	}

	GetWorldTransform().UpdateMatrix();
}
