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


	bool GetIsDead() const { return isDead_; }

	void OnCollision(const CollisionInfo& info) override;

private:

	//�f�X�t���O
	bool isDead_ = false;

	// ���f��
	Model* bossModel = nullptr;
};
