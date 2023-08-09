#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include "BossBullet.h"

//GameScene�̑O���錾
class GameScene;

class Boss : public Object3d
{
public:
	//�f�X�g���N�^
	~Boss();
	//������
	void BossInitialize();

	void Update()override;
	void Pop();
	void Attack();
	void Move();
	void ChangeState();

	bool GetIsDead() const { return isDead_; }

	void OnCollision(const CollisionInfo& info) override;
	bool GetIsInvisible() { return isInvisible; }
	float GetAlpha() { return bossAlpha; }
	int GetTimer() { return appearTimer; }
	float GetHP() { return hp; }
	

private:

	//�f�X�t���O
	bool isDead_ = false;
	bool isInvisible = true;
	//�^�C�}�[
	int appearTimer = 0;
	float bossAlpha = 0.0f;
	float hp;
	bool isHit;
	int hitTimer;
	int timeCount;
	int timer;
	
	//�{�X�s�����
	enum State {
		WAIT,
		SHOT
	};
	State state;

	// ���f��
	Model* bossModel = nullptr;
	//�e
	std::list<std::unique_ptr<BossBullet>> bullets_;
};
