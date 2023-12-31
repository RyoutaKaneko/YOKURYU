/**
 * @file Energy.cpp
 * @brief 必殺技に必要なエネルギー用クラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>
#include <iostream>
#include <random>

//GameSceneの前方宣言
class GameScene;

class Energy : public Object3d
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void EnergyInitialize(const std::string& model_);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void Update(Vector3 pos, Vector3 rot);

	void DeadEffect(Vector3 rot);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info) override;

	/// <summary>
	/// 死亡フラグを取得
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() const { return isDead; }

private:
	// モデル
	Model* energyModel = nullptr;

	std::random_device seed_gen;
	Vector3 randomNum;
	
	bool isDead;
};
