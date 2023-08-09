#pragma once
#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include "BossBullet.h"

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
	
	//ボス行動情報
	enum State {
		WAIT,
		SHOT
	};
	State state;

	// モデル
	Model* bossModel = nullptr;
	//弾
	std::list<std::unique_ptr<BossBullet>> bullets_;
};
