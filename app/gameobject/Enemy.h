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

//GameScene�̑O���錾
class GameScene;

class Enemy : public Object3d
{
public:
	//�f�X�g���N�^
	~Enemy();
	//������
	void EnemyInitialize();


	bool GetIsDead() const { return isDead_; }
	
	void Update(Vector3 velo,float t);
	void EnemyDraw(ViewProjection* viewProjection_);

	void Attack();

	void OnCollision(const CollisionInfo& info) override;
	void SetStagePoint(float pos_) { stagePoint = pos_; }
	float GetStagePoint(){return stagePoint;}
	Object3d* GetPointer() { return this; }
	bool GetIsInvisible() { return isInvisible; }

	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

private:

	//�f�X�t���O
	bool isDead_ = false;
	//
	bool isInvisible = true;

	//�G
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// ���f��
	Model* enemyModel = nullptr;
	float alpha;

	//���a
	int timer;
	float radius = 1.0f;
	int coolTime = 0;
	float stagePoint;

	bool isAttack;
	int timeCount;
};
