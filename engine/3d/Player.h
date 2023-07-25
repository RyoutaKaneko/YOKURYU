#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"
#include "Particle.h"
#include "PlayerBullet.h"

struct LockInfo {
	Vector3 vec = {0,0,0};
	 Object3d* obj = nullptr;
};

class Player : public Object3d
{
public:
	//デストラクタ
	~Player();
	//初期化
	bool PlayerInitialize();

	void Update(Vector3 velo, std::vector<LockInfo>& info);

	void Move();
	///</summary>
	void Attack(Vector3 velo);
	void LockAttack(std::vector<LockInfo>& info);
	void PlayerDraw(ViewProjection* viewProjection_);

	//衝突時コールバック関数
	void OnCollision(const CollisionInfo& info) override;


	/////getter/////
	//hp
	int GetHP() { return hp; }
	bool GetIsHit() { return isHit; }
	bool GetIsShooted() { return isShooted; }
	//fever
	float GetLen() { return len; }

	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }


private:
	Input* input = nullptr;
	// モデル
	Model* playerModel = nullptr;
	//パーティクル
	Particle* particle = nullptr;
	//弾 
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	//HP
	int hp = 5;
	int coolTime = 0;
	float len = 6;
	int pTimer = 0;
	bool isHit;
	bool isShooted;
	int hitTime;

};
