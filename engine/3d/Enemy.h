#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>

//GameSceneの前方宣言
class GameScene;

class Enemy : public Object3d
{
public:
	//デストラクタ
	~Enemy();
	//初期化
	void EnemyInitialize();

	//敵リスト
	const std::list<std::unique_ptr<Enemy>>& GetEnemys() { return enemys_; }


	bool GetIsDead() const { return isDead_; }
	
	void Update();

	void OnCollision(const CollisionInfo& info) override;

private:

	//デスフラグ
	bool isDead_ = false;

	//敵
	std::list<std::unique_ptr<Enemy>> enemys_;

	// モデル
	Model* enemyModel = nullptr;

	//半径
	int timer;
	float radius = 1.0f;
};
