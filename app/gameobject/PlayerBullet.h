/**
 * @file PlayerBullet.cpp
 * @brief �v���C���[�̍U���Ɏg���e���X�g�p�N���X
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

namespace MyEngine {
	class PlayerBullet : public Object3d
	{
	public:
		///< summary>
		///������
		///</summary>
		void BulletInitialize(const Vector3& velocity);

		///< summary>
		///������
		///</summary>
		void Update();

		/// <summary>
		///�z�[�~���O�e�x�N�g��
		/// </summary>
		void HomingVec();

		/// <summary>
		/// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
		/// </summary>
		/// <param name="info">�Փˏ��</param>
		void OnCollision(const CollisionInfo& info) override;


	public:
		/// <summary>
		/// ���S�t���O�擾
		/// </summary>
		/// <returns></returns>
		bool IsDead() const { return isDead_; }


		/// <summary>
		/// �z�[�~���O�U�����ǂ���
		/// </summary>
		/// <returns></returns>
		bool GetIsHoming() { return isHoming; }

		/// <summary>
		/// �z�[�~���O�U�����ǂ���
		/// </summary>
		/// <param name="isHoming_"></param>
		void SetisHoming(bool isHoming_) { isHoming = isHoming_; }

		/// <summary>
		/// ���b�N�I������ݒ�
		/// </summary>
		/// <param name="obj"></param>
		void SetLock(Object3d* obj) { lockObj = obj; }

		/// <summary>
		/// �z�[�~���O����player�̍��W�Z�b�g
		/// </summary>
		/// <param name="playerPos_"></param>
		void SetPlayerPos(const Vector3& playerPos_) { playerPos = playerPos_; }

		//�萔
	private:
		static const float correction;
		static const int HOMING_TIME;
		static const float ADD_ACCEL;

	private:
		//���f��
		Model* bulletModel = nullptr;

		//���x
		Vector3 velocity_;

		//����
		static const int32_t kLifeTime = 60 * 8;
		//�f�X�^�C�}�[
		int32_t deathTimer_ = kLifeTime;
		//�f�X�t���O
		bool isDead_ = false;
		bool isHoming = false;
		int homingTime;
		float accel;
		Object3d* lockObj = nullptr;
		//�z�[�~���O����player�̍��W
		Vector3 playerPos;
		//�z�[�~���O���̌v�Z���W
		Vector3 lockPos;
	};
}
