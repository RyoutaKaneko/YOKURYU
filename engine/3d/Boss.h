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

	void Update()override;
	void Pop();

	bool GetIsDead() const { return isDead_; }

	void OnCollision(const CollisionInfo& info) override;
	bool GetIsInvisible() { return isInvisible; }
	float GetAlpha() { return bossAlpha; }
	int GetTimer() { return appearTimer; }
	float GetHP() { return hp; }
	

private:

	//デスフラグ
	bool isDead_ = false;
	bool isInvisible = true;
	//タイマー
	int appearTimer = 0;
	float bossAlpha = 0.0f;
	float hp;
	bool isHit;
	int hitTimer;
	int timeCount;
	int timer;

	// モデル
	Model* bossModel = nullptr;
};
