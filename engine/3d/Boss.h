#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"

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

	bool GetIsDead() const { return isDead_; }

	void OnCollision(const CollisionInfo& info) override;
	bool GetIsInvisible() { return isInvisible; }
	float GetAlpha() { return bossAlpha; }
	int GetTimer() { return bossTimer; }
	

private:

	//�f�X�t���O
	bool isDead_ = false;
	bool isInvisible = true;
	//�^�C�}�[
	int bossTimer = 0;
	float bossAlpha = 0.0f;

	// ���f��
	Model* bossModel = nullptr;
};
