/**
 * @file BombEnemy.h
 * @brief �˂�����ł��Ĕ�������G�N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Enemy.h"
#include "BaseCollider.h"

namespace MyEngine {
	class BombEnemy : public Enemy
	{
	public:
		~BombEnemy();

		/// <summary>
		/// ������
		/// </summary>
		void BombInitialize();

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="velo">player���W</param>
		/// <param name="t">�v���C���[�ʉߓ_</param>
		void BombUpdate(const Vector3& pPos, MyEngine::RailCamera* rail);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="viewProjection_">�J����</param>
		void BombDraw(ViewProjection* viewProjection_);

		/// <summary>
		/// �U��
		/// </summary>
		void BombAttack(const Vector3& pPos);

		/// <summary>
		/// �����蔻��
		/// </summary>
		/// <param name="info">�Փˏ��</param>
		void OnCollision(const CollisionInfo& info) override;

	private:
		float popTime;
	};
}

