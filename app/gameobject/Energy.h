/**
 * @file Energy.cpp
 * @brief �K�E�Z�ɕK�v�ȃG�l���M�[�p�N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>

//GameScene�̑O���錾
class GameScene;

class Energy : public Object3d
{
public:

	void EnergyInitialize();
	
	void Update(Vector3 pos, Vector3 rot);

	void OnCollision(const CollisionInfo& info) override;

	bool GetIsDead() const { return isDead; }

private:
	// ���f��
	Model* energyModel = nullptr;
	
	bool isDead;
};
