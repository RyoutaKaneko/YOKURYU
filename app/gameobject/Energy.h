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
#include <iostream>
#include <random>

//GameScene�̑O���錾
class GameScene;

class Energy : public Object3d
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void EnergyInitialize(const std::string& model_);

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void Update(Vector3 pos, Vector3 rot);

	void DeadEffect();

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	void OnCollision(const CollisionInfo& info) override;

	/// <summary>
	/// ���S�t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead; }

private:
	// ���f��
	Model* energyModel = nullptr;

	std::random_device seed_gen;
	Vector3 randomNum;
	
	bool isDead;
};
