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
	/// <param name="rot">��]</param>
	void Update(Vector3 rot);

	/// <summary>
	/// ���S�t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead; }

private:
	static const Vector3 ROTATE;
	static const Vector3 SUB_SCALE;
	static const float MIN_SCALE;

private:
	// ���f��
	Model* energyModel = nullptr;

	std::random_device seed_gen;
	Vector3 randomNum;
	
	bool isDead;
};
