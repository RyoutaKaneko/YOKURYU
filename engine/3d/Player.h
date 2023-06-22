#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"
#include "Particle.h"


class Player : public Object3d
{
public:
	//デストラクタ
	~Player();
	//初期化
	bool PlayerInitialize();

	void Update(std::vector <Vector3>& point);

	void Move(std::vector <Vector3>& point);

	//衝突時コールバック関数
	/*void OnCollision(const CollisionInfo& info) override;
	void OffCollision(const CollisionInfo& info) override;*/


	//hp
	int GetHP() { return hp; }

	//fever
	float GetLen() { return len; }


private:
	Input* input = nullptr;
	// モデル
	Model* playerModel = nullptr;
	//パーティクル
	Particle* particle = nullptr;
	//HP
	int hp;

	float len;

};
