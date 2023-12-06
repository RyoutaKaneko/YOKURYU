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
	void Update(Vector3 velo,RailCamera* rail);

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
	float GetStagePoint(){return stagePoint;}

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
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

	/// <summary>
	/// ���S���o
	/// </summary>
	void PopParticle();

	bool GetIsParticle() { return isParticle; }

private:

	static const int DEATH_TIMER = 60;

	//�f�X�t���O
	bool isDead_ = false;
	//
	bool isInvisible = true;
	bool isParticle = false;

	//�G
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	std::list<std::unique_ptr<Energy>> deadParticles;

	// ���f��
	Model* enemyModel = nullptr;
	float alpha;

	//���a
	int timer;
	float radius = 1.0f;
	int coolTime = 0;
	float stagePoint;
	int deathTimer;

	bool isAttack;
	int timeCount;
};
