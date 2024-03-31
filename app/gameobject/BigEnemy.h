/**
 * @file BigEnemy.h
 * @brief �ł��G�N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Enemy.h"
#include "BaseCollider.h"

namespace MyEngine {
	class BigEnemy : public Enemy
	{
	public:
		~BigEnemy();

		/// <summary>
		/// ������
		/// </summary>
		void BigInitialize();

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="velo">player���W</param>
		/// <param name="t">�v���C���[�ʉߓ_</param>
		void BigUpdate(const Vector3& pPos, MyEngine::RailCamera* rail);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="viewProjection_">�J����</param>
		void BigDraw(ViewProjection* viewProjection_);

		/// <summary>
		/// �����蔻��
		/// </summary>
		/// <param name="info">�Փˏ��</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		/// ���S���G����
		/// </summary>
		bool GetPopReq() { return popReq; }

		/// <summary>
		/// ���S���G����
		/// </summary>
		void SetPopReq(const bool& req) { popReq = req; }

	private:
		bool popReq;
	};
}



