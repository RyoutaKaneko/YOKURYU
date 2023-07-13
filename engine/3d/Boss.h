#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"

//GameSceneの前方宣言
class GameScene;

class Boss : public Object3d
{
public:
	//デストラクタ
	~Boss();
	//初期化
	void BossInitialize();


	bool GetIsDead() const { return isDead_; }

	void OnCollision(const CollisionInfo& info) override;

private:

	//デスフラグ
	bool isDead_ = false;

	// モデル
	Model* bossModel = nullptr;
};
