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

	void Update(Vector3 velo);
	void Pop();
	void Attack();
	void Move();
	void ChangeState();
	
	void BossDraw(ViewProjection* viewProjection_);

	bool GetIsDead() const { return isDead_; }
	//�����蔻��
	void OnCollision(const CollisionInfo& info) override;
	//Getter
	bool GetIsInvisible() { return isInvisible; }
	float GetAlpha() { return bossAlpha; }
	int GetTimer() { return appearTimer; }
	float GetHP() { return hp; }
	int GetPartsNum() { return PARTS_NUM; }
	Object3d* GetParts(int i) { return parts[i]; }
	//���o�X�L�b�v
	void SkipMovie();

	

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
	static const int PARTS_NUM = 5;
	Object3d* parts[PARTS_NUM];
};
