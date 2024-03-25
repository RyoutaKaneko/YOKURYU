/**
 * @file Enemy.cpp
 * @brief enemy�̑S��(�X�e�[�^�X�A�s���A�`��)���܂Ƃ߂��N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>
#include "EnemyBullet.h"
#include "Energy.h"
#include "RailCamera.h"

//GameScene�̑O���錾
class GameScene;

namespace MyEngine {
	class Enemy : public Object3d
	{
	public:
		//�f�X�g���N�^
		~Enemy();

		/// <summary>
		/// ������
		/// </summary>
		void EnemyInitialize();

		/// <summary>
		/// ���S�t���O���擾
		/// </summary>
		/// <returns></returns>
		bool GetIsDead() const { return isDead_; }

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="velo">�e�x�N�g��</param>
		/// <param name="t">�v���C���[�ʉߓ_</param>
		void Update(const Vector3& velo, MyEngine::RailCamera* rail);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="viewProjection_">�J����</param>
		void EnemyDraw(ViewProjection* viewProjection_);

		/// <summary>
		/// �U��
		/// </summary>
		void Attack();

		/// <summary>
		/// �����蔻��
		/// </summary>
		/// <param name="info">�Փˏ��</param>
		void OnCollision(const CollisionInfo& info) override;

		/// <summary>
		///  �o���ʒu��ݒ�
		/// </summary>
		/// <param name="pos_">�o���ʒu</param>
		void SetStagePoint(float pos_) { stagePoint = pos_; }

		/// <summary>
		/// �o���ʒu���擾
		/// </summary>
		/// <returns></returns>
		float GetStagePoint() { return stagePoint; }

		/// <summary>
		/// �G�I�u�W�F�N�g�|�C���^���擾
		/// </summary>
		/// <returns></returns>
		Object3d* GetPointer() { return this; }

		/// <summary>
		/// �G�o����Ԃ��擾
		/// </summary>
		/// <returns></returns>
		bool GetIsInvisible() { return isInvisible; }

		/// <summary>
		/// �e���X�g���擾
		/// </summary>
		/// <returns></returns>
		const std::list<std::unique_ptr<MyEngine::EnemyBullet>>& GetBullets() { return bullets_; }

		/// <summary>
		/// ���S���o
		/// </summary>
		void PopParticle();

		//�q�b�g����
		bool GetIsHit() { return isHit; }

		//�萔
	protected:
		static const int DEATH_TIMER = 50;
		static const float MOVE_POWER;
		static const float UPDOWN_POWER;
		static const float MAX_ALPHA;
		static const Vector3 ADDSCALE;
		static const float ATTACK_RANGE;
		static const int COOLTIME_MAX = 200;
		static const int SCALE_MAX = 3;
		static const int DEAD_PARTICLE = 45;
		static const int MOVE_TIME_ONE = 75;
		static const int MOVE_TIME_TWO = 150;
		static const int TIMECOUNT_MAX = 4;
		static const float POP_RANGE;
		static const float SHADOW_Y;

	protected:

		//�f�X�t���O
		bool isDead_ = false;
		bool isHit = false;
		//
		bool isInvisible = true;
		bool isParticle = false;

		//�G
		std::list<std::unique_ptr<MyEngine::EnemyBullet>> bullets_;
		std::list<std::unique_ptr<MyEngine::Energy>> deadParticles;
		Object3d* shadow = nullptr;

		// ���f��
		Model* enemyModel = nullptr;
		Model* shadowModel = nullptr;
		float alpha;

		//���a
		int timer;
		float radius = 1.0f;
		int coolTime = 0;
		float stagePoint;
		int deathTimer;
		float subAlpha = 0.2f;
		Vector3 rotePower;

		bool isAttack;
		int timeCount;
	};
}
