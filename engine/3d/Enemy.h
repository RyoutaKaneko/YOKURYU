#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>

//GameScene�̑O���錾
class GamePlayScene;

class Enemy : public Object3d
{
public:
	//�f�X�g���N�^
	~Enemy();
	//������
	void EnemyInitialize();

	//�G���X�g
	const std::list<std::unique_ptr<Enemy>>& GetEnemys() { return enemys_; }

	//gameScene��setter
	void SetGameScene(GamePlayScene* gameScene) { gameScene_ = gameScene; }

	bool GetIsDead() const { return isDead_; }
	
	void Update();

	/*void OnCollision(const CollisionInfo& info) override;
	void OffCollision(const CollisionInfo& info) override;*/

private:
	//�Q�[���V�[��
	GamePlayScene* gameScene_ = nullptr;

	//�f�X�t���O
	bool isDead_ = false;

	//�G
	std::list<std::unique_ptr<Enemy>> enemys_;

	// ���f��
	Model* enemyModel = nullptr;

	//���a
	int timer;
	float radius = 1.0f;
};