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

	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

private:

	//�f�X�t���O
	bool isDead_ = false;

	//�G
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// ���f��
	Model* enemyModel = nullptr;

	//���a
	int timer;
	float radius = 1.0f;
	int coolTime = 0;
	float stagePoint;

	bool isAttack;
	int timeCount;
};
