/**
 * @file EnemyBullet.cpp
 * @brief �ʏ�G�U���Ɏg���e���X�g�p�N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Vector3.h"
#include <Model.h>
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include "Object3d.h"

class EnemyBullet : public Object3d
{
public:
	///< summary>
	///������
	///</summary>
	void BulletInitialize();

	///< summary>
	///������
	///</summary>
	void Update(const Vector3& playerPos_, bool isDead);


	/// <summary>
	/// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	void OnCollision(const CollisionInfo& info) override;


public:
	/// <summary>
	/// ���S�t���O���擾
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isDead_; }

private:
	static const int HOMING_TIME = 25;

private:
	//���f��
	Model* bulletModel = nullptr;

	//���x
	Vector3 playerPos;
	Vector3 velocity;

	//����
	static const int32_t kLifeTime = 60 * 3;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	int bulletTime;
	//�f�X�t���O
	bool isDead_ = false;

};
